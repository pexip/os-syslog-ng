/*
 * Copyright (c) 2015 Balabit
 * Copyright (c) 2015 Balazs Scheidler <balazs.scheidler@balabit.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */
#include "python-helpers.h"
#include "scratch-buffers.h"
#include "str-utils.h"
#include "messages.h"

const gchar *
_py_get_callable_name(PyObject *callable, gchar *buf, gsize buf_len)
{
  PyObject *name = PyObject_GetAttrString(callable, "__name__");

  if (name && _py_is_string(name))
    {
      g_strlcpy(buf, _py_get_string_as_string(name), buf_len);
    }
  else
    {
      PyErr_Clear();
      g_strlcpy(buf, "<unknown>", buf_len);
    }
  Py_XDECREF(name);
  return buf;
}

void
_py_log_python_traceback_to_stderr(void)
{
  PyObject *traceback_module = NULL;
  PyObject *print_exception = NULL;
  PyObject *res = NULL;
  PyObject *exc, *value, *tb;

  PyErr_Fetch(&exc, &value, &tb);
  if (!exc)
    return;

  traceback_module = _py_do_import("traceback");
  if (!traceback_module)
    goto exit;
  print_exception = PyObject_GetAttrString(traceback_module, "print_exception");
  if (!print_exception)
    {
      msg_error("Error printing proper Python traceback for the exception, traceback.print_exception function not found");
      PyErr_Print();
      PyErr_Clear();
      goto exit;
    }
  res = PyObject_CallFunction(print_exception, "OOO", exc, value, tb ? : Py_None);
  if (!res)
    {
      msg_error("Error printing proper Python traceback for the exception, printing the error caused by print_exception() itself");
      PyErr_Print();
      PyErr_Clear();
    }
exit:
  Py_XDECREF(res);
  Py_XDECREF(print_exception);
  Py_XDECREF(traceback_module);
  PyErr_Restore(exc, value, tb);
}

const gchar *
_py_format_exception_text(gchar *buf, gsize buf_len)
{
  PyObject *exc, *value, *tb, *str;

  PyErr_Fetch(&exc, &value, &tb);
  if (!exc)
    {
      g_strlcpy(buf, "None", buf_len);
      return buf;
    }
  PyErr_NormalizeException(&exc, &value, &tb);

  str = PyObject_Str(value);
  if (!str)
    PyErr_Clear();

  if (str && _py_is_string(str))
    {
      g_snprintf(buf, buf_len, "%s: %s", ((PyTypeObject *) exc)->tp_name, _py_get_string_as_string(str));
    }
  else
    {
      g_strlcpy(buf, "<unknown>", buf_len);
    }
  Py_XDECREF(str);
  PyErr_Restore(exc, value, tb);
  return buf;
}

void
_py_finish_exception_handling(void)
{
  _py_log_python_traceback_to_stderr();
  PyErr_Clear();
}

PyObject *
_py_get_attr_or_null(PyObject *o, const gchar *attr)
{
  PyObject *result;

  if (!attr)
    return NULL;

  result = PyObject_GetAttrString(o, attr);
  if (!result)
    {
      PyErr_Clear();
      return NULL;
    }
  return result;
}

PyObject *
_py_do_import(const gchar *modname)
{
  PyObject *module, *modobj;

  module = PyUnicode_FromString(modname);
  if (!module)
    {
      msg_error("Error allocating Python string",
                evt_tag_str("string", modname));
      return NULL;
    }

  modobj = PyImport_Import(module);
  Py_DECREF(module);
  if (!modobj)
    {
      gchar buf[256];

      msg_error("Error loading Python module",
                evt_tag_str("module", modname),
                evt_tag_str("exception", _py_format_exception_text(buf, sizeof(buf))));
      _py_finish_exception_handling();
      return NULL;
    }
  return modobj;
}

gboolean
_split_fully_qualified_name(const gchar *input, gchar **module, gchar **class)
{
  const gchar *p;

  for (p = input + strlen(input) - 1; p > input && *p != '.'; p--)
    ;

  if (p > input)
    {
      *module = g_strndup(input, (p - input));
      *class = g_strdup(p + 1);
      return TRUE;
    }
  return FALSE;
}

PyObject *
_py_resolve_qualified_name(const gchar *name)
{
  PyObject *module, *value = NULL;
  gchar *module_name, *attribute_name;

  if (!_split_fully_qualified_name(name, &module_name, &attribute_name))
    {
      module_name = g_strdup("_syslogng_main");
      attribute_name = g_strdup(name);
    }

  module = _py_do_import(module_name);
  if (!module)
    goto exit;

  value = _py_get_attr_or_null(module, attribute_name);
  Py_DECREF(module);

exit:
  g_free(module_name);
  g_free(attribute_name);
  return value;
}

static void
_insert_to_dict(gpointer key, gpointer value, gpointer dict)
{
  PyObject *key_pyobj = _py_string_from_string((gchar *) key, -1);
  PyObject *value_pyobj = _py_string_from_string((gchar *) value, -1);
  PyDict_SetItem( (PyObject *) dict, key_pyobj, value_pyobj);
}

PyObject *
_py_create_arg_dict(GHashTable *args)
{
  PyObject *arg_dict = PyDict_New();
  g_hash_table_foreach(args, _insert_to_dict, arg_dict);
  return arg_dict;
}

PyObject *
_py_invoke_function(PyObject *func, PyObject *arg, const gchar *class, const gchar *caller_context)
{
  PyObject *ret;

  ret = PyObject_CallFunctionObjArgs(func, arg, NULL);
  if (!ret)
    {
      gchar buf1[256], buf2[256];

      msg_error("Exception while calling a Python function",
                evt_tag_str("caller", caller_context),
                evt_tag_str("class", class),
                evt_tag_str("function", _py_get_callable_name(func, buf1, sizeof(buf1))),
                evt_tag_str("exception", _py_format_exception_text(buf2, sizeof(buf2))));
      _py_finish_exception_handling();
      return NULL;
    }
  return ret;
}

PyObject *
_py_invoke_function_with_args(PyObject *func, PyObject *args, const gchar *class, const gchar *caller_context)
{
  PyObject *ret;

  ret = PyObject_CallObject(func, args);
  if (!ret)
    {
      gchar buf1[256], buf2[256];

      msg_error("Exception while calling a Python function",
                evt_tag_str("caller", caller_context),
                evt_tag_str("class", class),
                evt_tag_str("function", _py_get_callable_name(func, buf1, sizeof(buf1))),
                evt_tag_str("exception", _py_format_exception_text(buf2, sizeof(buf2))));
      _py_finish_exception_handling();
      return NULL;
    }
  return ret;
}

void
_py_invoke_void_function(PyObject *func, PyObject *arg, const gchar *class, const gchar *caller_context)
{
  PyObject *ret = _py_invoke_function(func, arg, class, caller_context);
  Py_XDECREF(ret);
}

gboolean
_py_invoke_bool_function(PyObject *func, PyObject *arg, const gchar *class, const gchar *caller_context)
{
  PyObject *ret;
  gboolean result = FALSE;

  ret = _py_invoke_function(func, arg, class, caller_context);
  if (ret)
    result = PyObject_IsTrue(ret);
  Py_XDECREF(ret);
  return result;
}

PyObject *
_py_get_optional_method(PyObject *instance, const gchar *class, const gchar *method_name, const gchar *module)
{
  PyObject *method = _py_get_attr_or_null(instance, method_name);
  if (!method)
    {
      msg_debug("Missing optional Python method",
                evt_tag_str("module", module),
                evt_tag_str("class", class),
                evt_tag_str("method", method_name));
      return NULL;
    }
  return method;
}

PyObject *
_py_invoke_method_by_name(PyObject *instance, const gchar *method_name, PyObject *arg, const gchar *class,
                          const gchar *module)
{
  PyObject *method = _py_get_optional_method(instance, class, method_name, module);

  if (!method)
    return NULL;

  PyObject *ret = _py_invoke_function(method, arg, class, module);
  Py_DECREF(method);

  return ret;
}

void
_py_invoke_void_method_by_name(PyObject *instance, const gchar *method_name, const gchar *class, const gchar *module)
{
  PyObject *method = _py_get_optional_method(instance, class, method_name, module);
  if (method)
    {
      _py_invoke_void_function(method, NULL, class, module);
      Py_DECREF(method);
    }
}

gboolean
_py_invoke_bool_method_by_name_with_args(PyObject *instance, const gchar *method_name,
                                         GHashTable *args, const gchar *class, const gchar *module)
{
  gboolean result = FALSE;
  PyObject *method = _py_get_optional_method(instance, class, method_name, module);

  if (method)
    {
      PyObject *args_obj = args ? _py_create_arg_dict(args) : NULL;
      result = _py_invoke_bool_function(method, args_obj, class, module);

      Py_XDECREF(args_obj);
      Py_DECREF(method);
    }
  return result;
}

gboolean
_py_invoke_bool_method_by_name(PyObject *instance, const gchar *method_name, const gchar *class, const gchar *module)
{
  return _py_invoke_bool_method_by_name_with_args(instance, method_name, NULL, class, module);
}

static void
_foreach_import(gpointer data, gpointer user_data)
{
  gchar *modname = (gchar *) data;
  PyObject *mod;

  mod = _py_do_import(modname);
  Py_XDECREF(mod);
}

void
_py_perform_imports(GList *imports)
{
  g_list_foreach(imports, _foreach_import, NULL);
}

gboolean
_py_is_string(PyObject *object)
{
  return PyBytes_Check(object) || PyUnicode_Check(object);
}


/* NOTE: this function returns a managed memory area pointing to an utf8
 * representation of the string, with the following constraints:
 *
 *   1) we basically assume that non-unicode strings (both in Python2 and
 *   Python3) are in utf8 or at least utf8 compatible (e.g.  ascii).  It
 *   doesn't really make sense otherwise.  If we don't the resulting string
 *   is not going to be utf8, rather it would be the system codepage.
 *
 *   2) in the case of Python3 we are using the utf8 cache in the unicode
 *   instance.  In the case of Python2 we are allocating a scratch buffer to
 *   hold the data for us.
 **/

const gchar *
_py_get_string_as_string(PyObject *object)
{
  if (PyBytes_Check(object))
    return PyBytes_AsString(object);
#if PY_MAJOR_VERSION >= 3
  else if (PyUnicode_Check(object))
    return PyUnicode_AsUTF8(object);
#elif PY_MAJOR_VERSION < 3
  else if (PyUnicode_Check(object))
    {
      PyObject *utf8_bytes = PyUnicode_AsUTF8String(object);
      GString *buffer = scratch_buffers_alloc();
      g_string_assign_len(buffer, PyBytes_AsString(utf8_bytes), PyBytes_Size(utf8_bytes));
      Py_XDECREF(utf8_bytes);
      return buffer->str;
    }
#endif
  g_assert_not_reached();
}

PyObject *
_py_string_from_string(const gchar *str, gssize len)
{
#if PY_MAJOR_VERSION >= 3
  const gchar *charset;

  /* NOTE: g_get_charset() returns if the current character set is utf8 */
  if (g_get_charset(&charset))
    {
      if (len < 0)
        return PyUnicode_FromString(str);
      else
        return PyUnicode_FromStringAndSize(str, len);
    }
  else
    {
      GError *error = NULL;
      gsize bytes_read, bytes_written;
      gchar *utf8_string;
      PyObject *res;

      utf8_string = g_locale_to_utf8(str, len, &bytes_read, &bytes_written, &error);
      if (utf8_string)
        {
          res = PyUnicode_FromStringAndSize(utf8_string, bytes_written);
          g_free(utf8_string);
          return res;
        }
      else
        {
          g_error_free(error);
          if (len >= 0)
            return PyBytes_FromStringAndSize(str, len);
          else
            return PyBytes_FromString(str);
        }
    }
#elif PY_MAJOR_VERSION < 3
  if (len >= 0)
    return PyBytes_FromStringAndSize(str, len);
  else
    return PyBytes_FromString(str);
#endif
}

void
py_slng_generic_dealloc(PyObject *self)
{
  Py_TYPE(self)->tp_free(self);
}
