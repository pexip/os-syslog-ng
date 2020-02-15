/*
 * Copyright (c) 2017 Balabit
 * Copyright (c) 2017 Zoltan Pallagi <zoltan.pallagi@balabit.com>
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

package org.syslog_ng.hdfs;

import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.Path;

import java.io.IOException;

public class HdfsFile {
    private FSDataOutputStream fsDataOutputStream;
    private Path path;
    private long lastWrite;

    public HdfsFile(Path filepath, FSDataOutputStream outputstream) {
        this.path = filepath;
        this.fsDataOutputStream = outputstream;
        this.lastWrite = 0;
    }

    public Path getPath() {
        return path;
    }

    public boolean isOpen() {
        return fsDataOutputStream != null;
    }

    public void flush() throws IOException {
         if (!isOpen())
            return;

         fsDataOutputStream.hflush();
         fsDataOutputStream.hsync();
    }

    public void write(byte[] message) throws IOException {
         if (!isOpen())
            throw new IOException("File is not open: "+path);

         fsDataOutputStream.write(message);

         lastWrite = System.currentTimeMillis();
    }

    public long timeSinceLastWrite() {
       if (!isOpen())
          return 0;

       return System.currentTimeMillis() - lastWrite;
    }

    public void close() throws IOException {
         if (!isOpen())
            return;

          fsDataOutputStream.close();
          fsDataOutputStream = null;
          lastWrite = 0;
    }
}
