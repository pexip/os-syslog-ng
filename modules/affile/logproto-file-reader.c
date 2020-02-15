/*
 * Copyright (c) 2017 Balabit
 * Copyright (c) 2017 Balázs Scheidler
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

#include "logproto-file-reader.h"
#include "logproto/logproto-record-server.h"
#include "logproto/logproto-multiline-server.h"

LogProtoServer *
log_proto_file_reader_new(LogTransport *transport, const LogProtoFileReaderOptions *options)
{
  if (options->pad_size > 0)
    return log_proto_padded_record_server_new(transport, &options->super.super, options->pad_size);
  else
    return log_proto_multiline_server_new(transport, &options->super);
}

void
log_proto_file_reader_options_defaults(LogProtoFileReaderOptions *options)
{
  log_proto_multi_line_server_options_defaults(&options->super);
  options->pad_size = 0;
}

void
log_proto_file_reader_options_init(LogProtoFileReaderOptions *options)
{
  log_proto_multi_line_server_options_init(&options->super);
}

void
log_proto_file_reader_options_destroy(LogProtoFileReaderOptions *options)
{
  log_proto_multi_line_server_options_destroy(&options->super);
}
