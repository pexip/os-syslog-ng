/*
 * Copyright (c) 2015 Balabit
 * Copyright (c) 2015 Viktor Juhasz <viktor.juhasz@balabit.com>
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

package org.syslog_ng.elasticsearch.messageprocessor;

import org.elasticsearch.ElasticsearchException;
import org.elasticsearch.action.index.IndexRequest;
import org.elasticsearch.action.index.IndexResponse;
import org.syslog_ng.elasticsearch.client.ESClient;
import org.syslog_ng.elasticsearch.ElasticSearchOptions;

public class ESSingleMessageProcessor extends ESMessageProcessor {

	public ESSingleMessageProcessor(ElasticSearchOptions options, ESClient client) {
		super(options, client);
	}

	@Override
	public boolean send(IndexRequest req) {
		try {
			IndexResponse response = client.getClient().index(req).actionGet();
			logger.debug("Message inserted with id: " + response.getId());
			return true;
		}
		catch (ElasticsearchException e) {
			logger.error("Failed to send message: " + e.getMessage());
			return false;
		}
	}

}
