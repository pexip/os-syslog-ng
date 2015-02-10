#include "parse-number.h"

#include <string.h>
#include <errno.h>
#include <stdlib.h>

static gboolean
_valid_unit(const gchar unit_char)
{
  return (unit_char == 'B' || unit_char == 'b');
}

static gboolean
_valid_exponent(const gchar exponent_char)
{
  gchar e = exponent_char;

  return e == 'k' || e == 'K' ||
         e == 'm' || e == 'M' ||
         e == 'g' || e == 'G';
}

static gboolean
_parse_suffix(const gchar *suffix, gchar *exponent_char, gchar *base_char, gchar *unit_char)
{
  gint suffix_len;

  suffix_len = strlen(suffix);
  if (suffix_len > 3)
    return FALSE;
  if (suffix_len == 0)
    return TRUE;

  if (suffix_len == 3)
    {
      *exponent_char = suffix[0];
      *base_char = suffix[1];
      *unit_char = suffix[2];
    }
  else if (suffix_len == 2)
    {
      *exponent_char = suffix[0];
      if (_valid_unit(suffix[1]))
        *unit_char = suffix[1];
      else
        *base_char = suffix[1];
    }
  else if (suffix_len == 1)
    {
      if (_valid_exponent(suffix[0]))
        *exponent_char = suffix[0];
      else if (_valid_unit(suffix[0]))
        *unit_char = suffix[0];
      else
        return FALSE;
    }
  return TRUE;
}

static gboolean
_determine_multiplier(gchar base_char, gint *multiplier)
{
  if (base_char == 0)
    *multiplier = 1000;
  else if (base_char == 'I' || base_char == 'i')
    *multiplier = 1024;
  else
    return FALSE;
  return TRUE;
}

static gboolean
_validate_unit(gchar unit_char)
{
  if (unit_char && !_valid_unit(unit_char))
    return FALSE;
  return TRUE;
}

static gboolean
_process_exponent(gchar exponent_char, gint64 *d, gint multiplier)
{
  switch (exponent_char)
    {
    case 'G':
    case 'g':
      (*d) *= multiplier;
    case 'm':
    case 'M':
      (*d) *= multiplier;
    case 'K':
    case 'k':
      (*d) *= multiplier;
    case 0:
      return TRUE;
    default:
      return FALSE;
    }
}

static gboolean
_process_suffix(const gchar *suffix, gint64 *d)
{
  gchar exponent_char = 0, base_char = 0, unit_char = 0;
  gint multiplier = 0;

  if (!_parse_suffix(suffix, &exponent_char, &base_char, &unit_char))
    return FALSE;

  if (!_determine_multiplier(base_char, &multiplier))
    return FALSE;

  if (!_validate_unit(unit_char))
    return FALSE;

  if (!_process_exponent(exponent_char, d, multiplier))
    return FALSE;

  return TRUE;
}

static gboolean
_parse_number(const gchar *s, gchar **endptr, gint64 *d)
{
  gint64 val;

  errno = 0;
  val = strtoll(s, endptr, 10);

  if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
      || (errno != 0 && val == 0))
    return FALSE;

  if (*endptr == s)
    return FALSE;

  *d = val;
  return TRUE;
}

gboolean
parse_number(const gchar *s, gint64 *d)
{
  gchar *endptr;

  if (!_parse_number(s, &endptr, d))
    return FALSE;
  if (*endptr)
    return FALSE;
  return TRUE;
}

gboolean
parse_number_with_suffix(const gchar *s, gint64 *d)
{
  gchar *endptr;

  if (!_parse_number(s, &endptr, d))
    return FALSE;
  return _process_suffix(endptr, d);
}
