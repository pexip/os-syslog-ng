/*
 * Copyright (c) 2002-2013, 2015 Balabit
 * Copyright (c) 1998-2013, 2015 Balázs Scheidler
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
#ifndef PATTERNDB_PDB_PROGRAM_H_INCLUDED
#define PATTERNDB_PDB_PROGRAM_H_INCLUDED

#include "syslog-ng.h"
#include "radix.h"

/*
 * This class encapsulates a set of program related rules in the
 * pattern database. Its instances are stored as "value" in the
 * program name RADIX tree. It basically contains another RADIX for
 * the per-program patterns.
 */
typedef struct _PDBProgram
{
  guint ref_cnt;
  RNode *rules;
} PDBProgram;

PDBProgram *pdb_program_new(void);
PDBProgram *pdb_program_ref(PDBProgram *self);
void pdb_program_unref(PDBProgram *s);

#endif
