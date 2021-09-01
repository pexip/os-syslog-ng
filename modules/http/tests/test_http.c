/*
 * Copyright (c) 2018 Balabit
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#include <syslog-ng.h>
#include <logmsg/logmsg.h>
#include <apphook.h>
#include "http.h"
#include "http-worker.h"
#include "logthrdest/logthrdestdrv.h"

#include <criterion/criterion.h>
#include <criterion/parameterized.h>

TestSuite(http, .init = app_startup, .fini = app_shutdown);

struct http_action_test_params
{
  glong http_code;
  char *explanation;
  LogThreadedResult expected_value;
};

ParameterizedTestParameters(http, http_code_tests)
{
  static struct http_action_test_params params[] =
  {
    { 100, "Continue", LTR_NOT_CONNECTED},
    { 101, "Switching Protocols", LTR_NOT_CONNECTED},
    { 102, "Processing", LTR_ERROR},
    { 103, "Early Hints", LTR_ERROR},

    { 200, "OK", LTR_SUCCESS},
    { 201, "Created", LTR_SUCCESS},
    { 202, "Accepted", LTR_SUCCESS},
    { 203, "Non-Authoritative Information", LTR_SUCCESS},
    { 204, "No Content", LTR_SUCCESS},
    { 205, "Reset Content", LTR_SUCCESS},
    { 206, "Partial Content", LTR_SUCCESS},

    { 300, "Multiple Choices", LTR_NOT_CONNECTED},
    { 301, "Moved Permanently", LTR_NOT_CONNECTED},
    { 302, "Found", LTR_NOT_CONNECTED},
    { 303, "See Other", LTR_NOT_CONNECTED},
    { 304, "Not Modified", LTR_ERROR},
    { 307, "Temporary Redirect", LTR_NOT_CONNECTED},
    { 308, "Permanent Redirect", LTR_NOT_CONNECTED},

    { 400, "Bad Request", LTR_NOT_CONNECTED},
    { 401, "Unauthorized", LTR_NOT_CONNECTED},
    { 402, "Payment Required", LTR_NOT_CONNECTED},
    { 403, "Forbidden", LTR_NOT_CONNECTED},
    { 404, "Not Found", LTR_NOT_CONNECTED},
    { 405, "Method Not Allowed", LTR_NOT_CONNECTED},
    { 406, "Not Acceptable", LTR_NOT_CONNECTED},
    { 407, "Proxy Authentication Required", LTR_NOT_CONNECTED},
    { 408, "Request Timeout", LTR_NOT_CONNECTED},
    { 409, "Conflict", LTR_NOT_CONNECTED},
    { 410, "Gone", LTR_DROP},
    { 411, "Length Required", LTR_NOT_CONNECTED},
    { 412, "Precondition Failed", LTR_NOT_CONNECTED},
    { 413, "Payload Too Large", LTR_NOT_CONNECTED},
    { 414, "URI Too Long", LTR_NOT_CONNECTED},
    { 415, "Unsupported Media Type", LTR_NOT_CONNECTED},
    { 416, "Range Not Satisfiable", LTR_DROP},
    { 417, "Expectation Failed", LTR_NOT_CONNECTED},
    { 418, "I'm a teapot", LTR_NOT_CONNECTED},
    { 421, "Misdirected Request", LTR_NOT_CONNECTED},
    { 422, "Unprocessable Entity", LTR_DROP},
    { 423, "Locked", LTR_NOT_CONNECTED},
    { 424, "Failed Dependency", LTR_DROP},
    { 425, "Too Early", LTR_DROP},
    { 426, "Upgrade Required", LTR_NOT_CONNECTED},
    { 428, "Precondition Required", LTR_ERROR},
    { 429, "Too Many Requests", LTR_NOT_CONNECTED},
    { 431, "Request Header Fields Too Large", LTR_NOT_CONNECTED},
    { 451, "Unavailable For Legal Reasons", LTR_DROP},

    { 500, "Internal Server Error", LTR_NOT_CONNECTED},
    { 501, "Not Implemented", LTR_NOT_CONNECTED},
    { 502, "Bad Gateway", LTR_NOT_CONNECTED},
    { 503, "Service Unavailable", LTR_NOT_CONNECTED},
    { 504, "Gateway Timeout", LTR_ERROR},
    { 505, "HTTP Version Not Supported", LTR_NOT_CONNECTED},
    { 506, "Variant Also Negotiates", LTR_NOT_CONNECTED},
    { 507, "Insufficient Storage", LTR_NOT_CONNECTED},
    { 508, "Loop Detected", LTR_DROP},
    { 510, "Not Extended", LTR_NOT_CONNECTED},
    { 511, "Network Authentication Required", LTR_NOT_CONNECTED},

    // Some external values to test default behaviour
    { 199, "doesnotexist", LTR_NOT_CONNECTED},
    { 299, "doesnotexist", LTR_SUCCESS},
    { 399, "doesnotexist", LTR_NOT_CONNECTED},
    { 399, "doesnotexist", LTR_NOT_CONNECTED},
    { 599, "doesnotexist", LTR_NOT_CONNECTED}
  };

  return cr_make_param_array(struct http_action_test_params, params, sizeof(params)/sizeof(params[0]));
}

ParameterizedTest(struct http_action_test_params *param, http, http_code_tests)
{
  HTTPDestinationDriver *driver = (HTTPDestinationDriver *) http_dd_new(configuration);
  HTTPDestinationWorker *worker = (HTTPDestinationWorker *) http_dw_new(&driver->super, 0);
  const gchar *url = "http://dummy.url";

  LogThreadedResult res =  default_map_http_status_to_worker_status(worker, url, param->http_code);
  cr_assert_eq(res, param->expected_value,
               "code: %ld, explanation: %s, actual: %s, expected: %s",
               param->http_code, param->explanation, log_threaded_result_to_str(res),
               log_threaded_result_to_str(param->expected_value));

  log_threaded_dest_worker_free(&worker->super);
  log_pipe_unref((LogPipe *)driver);
}
