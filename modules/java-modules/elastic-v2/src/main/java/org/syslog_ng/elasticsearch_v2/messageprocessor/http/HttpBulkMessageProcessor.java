/*
 * Copyright (c) 2016 Balabit
 * Copyright (c) 2016 Laszlo Budai <laszlo.budai@balabit.com>
 * Copyright (c) 2016 Viktor Tusa <tusavik@gmail.com>
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

package org.syslog_ng.elasticsearch_v2.messageprocessor.http;

import io.searchbox.core.Bulk;
import io.searchbox.core.Index;
import io.searchbox.client.JestResult;
import org.syslog_ng.elasticsearch_v2.ElasticSearchOptions;
import org.syslog_ng.elasticsearch_v2.client.http.ESHttpClient;

import java.io.IOException;

public class HttpBulkMessageProcessor extends  HttpMessageProcessor {

	private Bulk.Builder bulk;

	public HttpBulkMessageProcessor(ElasticSearchOptions options, ESHttpClient client) {
		super(options, client);
		bulk = new Bulk.Builder();
	}

	@Override
	public boolean flush() {
		JestResult jestResult = null;
		logger.debug("Flushing messages for ES destination [mode=" + options.getClientMode() + "]");
		Bulk bulkActions = bulk.build();
		try {
			jestResult = client.getClient().execute(bulkActions);
		}
		catch (IOException e) {
			logger.error(e.getMessage());
			return false;
		}
		finally {
			bulk = new Bulk.Builder();
		}
		if (! jestResult.isSucceeded()) {
			logger.error(jestResult.getErrorMessage());
			return false;
		}
		return true;
	}

	@Override
	public boolean send(Index index) {
		bulk = bulk.addAction(index);
		return true;
	}
}
