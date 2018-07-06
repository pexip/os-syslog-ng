/*
 * Copyright (c) 2014 Balabit
 * Copyright (c) 2014 Viktor Juhasz <viktor.juhasz@balabit.com>
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
package org.syslog_ng;

public class DummyTextDestination extends TextLogDestination {

  private String name;

  public DummyTextDestination(long arg0) {
    super(arg0);
  }

  public void deinit() {
    InternalMessageSender.debug("Deinit");
  }

  public void onMessageQueueEmpty() {
    InternalMessageSender.debug("onMessageQueueEmpty");
    return;
  }

  public boolean init() {
    name = getOption("name");
    if (name == null) {
      InternalMessageSender.error("Name is a required option for this destination");
      return false;
    }
    InternalMessageSender.debug("Init " + name);
    return true;
  }

  public boolean open() {
    InternalMessageSender.debug("open");
    return true;
  }

  public boolean isOpened() {
    InternalMessageSender.debug("isOpened");
    return true;
  }

  public void close() {
    InternalMessageSender.debug("close");
  }

  public boolean send(String arg0) {
    InternalMessageSender.debug("Incoming message: " + arg0);
    return true;
  }

  @Override
  public String getNameByUniqOptions() {
    InternalMessageSender.debug("getNameByUniqOptions");
    return "DummyTextDestination";
  }

}
