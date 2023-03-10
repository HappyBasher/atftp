/*
 * argz.h
 *    Source file borrowed from glibc-2.2.3. This has been done to make
 *    atftp compile with uclibc, BSD, Solaris and other platform without
 *    glic
 *
 * $Id: argz.h,v 1.1 2003/01/21 01:38:35 jp Exp $
 *
 * Copyright (c) 2000 Jean-Pierre Lefebvre <helix@step.polymtl.ca>
 *                and Remi Lefebvre <remi@debian.org>
 *
 * atftp is free software; you can redistribute them and/or modify them
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 */

/* Routines for dealing with '\0' separated arg vectors.
   Copyright (C) 1995, 96, 97, 98, 99, 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _ARGZ_H
#define _ARGZ_H	1

#define __need_error_t
#include <errno.h>
#include <string.h>		/* Need size_t, and strchr is called below.  */

#ifndef __const
# define __const const
#endif

#ifndef __THROW
# define __THROW
#endif

#ifndef __BEGIN_DECLS
# define __BEGIN_DECLS
#endif

#ifndef __END_DECLS
# define __END_DECLS
#endif

#ifndef __attribute_pure__
# define __attribute_pure__
#endif

#ifndef __error_t_defined
typedef int error_t;
#endif

/* Make a '\0' separated arg vector from a unix argv vector, returning it in
   ARGZ, and the total length in LEN. If a memory allocation error occurs,
   ENOMEM is returned, otherwise 0. The result can be destroyed using free. */
extern error_t __argz_create (char *__const __argv[], char **__restrict __argz,
			      size_t *__restrict __len);
extern error_t argz_create (char *__const __argv[], char **__restrict __argz,
			    size_t *__restrict __len);

/* Make a '\0' separated arg vector from a SEP separated list in
   STRING, returning it in ARGZ, and the total length in LEN. If a
   memory allocation error occurs, ENOMEM is returned, otherwise 0.
   The result can be destroyed using free. */
extern error_t __argz_create_sep (__const char *__restrict __string,
				  int __sep, char **__restrict __argz,
				  size_t *__restrict __len);
extern error_t argz_create_sep (__const char *__restrict __string,
				int __sep, char **__restrict __argz,
				size_t *__restrict __len);

/* Returns the number of strings in ARGZ. */
extern size_t __argz_count (__const char *__argz, size_t __len)
     __attribute_pure__;
extern size_t argz_count (__const char *__argz, size_t __len)
     __attribute_pure__;

/* Puts pointers to each string in ARGZ into ARGV, which must be large enough
   to hold them all. */
extern void __argz_extract (__const char *__restrict __argz, size_t __len,
			    char **__restrict __argv);
extern void argz_extract (__const char *__restrict __argz, size_t __len,
			  char **__restrict __argv);

/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP. */
extern void __argz_stringify (char *__argz, size_t __len, int __sep);
extern void argz_stringify (char *__argz, size_t __len, int __sep);

/* Append BUF, of length BUF_LEN to the argz vector in ARGZ & ARGZ_LEN. */
extern error_t __argz_append (char **__restrict __argz,
			      size_t *__restrict __argz_len,
			      __const char *__restrict __buf, size_t _buf_len);
extern error_t argz_append (char **__restrict __argz,
			    size_t *__restrict __argz_len,
			    __const char *__restrict __buf, size_t __buf_len);

/* Append STR to the argz vector in ARGZ & ARGZ_LEN. */
extern error_t __argz_add (char **__restrict __argz,
			   size_t *__restrict __argz_len,
			   __const char *__restrict __str);
extern error_t argz_add (char **__restrict __argz,
			 size_t *__restrict __argz_len,
			 __const char *__restrict __str);

/* Append SEP separated list in STRING to the argz vector in ARGZ &
   ARGZ_LEN. */
extern error_t __argz_add_sep (char **__restrict __argz,
			       size_t *__restrict __argz_len,
			       __const char *__restrict __string, int __delim);
extern error_t argz_add_sep (char **__restrict __argz,
			     size_t *__restrict __argz_len,
			     __const char *__restrict __string, int __delim);

/* Delete ENTRY from ARGZ & ARGZ_LEN, if it appears there. */
extern void __argz_delete (char **__restrict __argz,
			   size_t *__restrict __argz_len,
			   char *__restrict __entry);
extern void argz_delete (char **__restrict __argz,
			 size_t *__restrict __argz_len,
			 char *__restrict __entry);

/* Insert ENTRY into ARGZ & ARGZ_LEN before BEFORE, which should be an
   existing entry in ARGZ; if BEFORE is NULL, ENTRY is appended to the end.
   Since ARGZ's first entry is the same as ARGZ, argz_insert (ARGZ, ARGZ_LEN,
   ARGZ, ENTRY) will insert ENTRY at the beginning of ARGZ. If BEFORE is not
   in ARGZ, EINVAL is returned, else if memory can't be allocated for the new
   ARGZ, ENOMEM is returned, else 0. */
extern error_t __argz_insert (char **__restrict __argz,
			      size_t *__restrict __argz_len,
			      char *__restrict __before,
			      __const char *__restrict __entry);
extern error_t argz_insert (char **__restrict __argz,
			    size_t *__restrict __argz_len,
			    char *__restrict __before,
			    __const char *__restrict __entry);

/* Replace any occurrences of the string STR in ARGZ with WITH, reallocating
   ARGZ as necessary. If REPLACE_COUNT is non-zero, *REPLACE_COUNT will be
   incremented by number of replacements performed. */
extern error_t __argz_replace (char **__restrict __argz,
			       size_t *__restrict __argz_len,
			       __const char *__restrict __str,
			       __const char *__restrict __with,
			       unsigned int *__restrict __replace_count);
extern error_t argz_replace (char **__restrict __argz,
			     size_t *__restrict __argz_len,
			     __const char *__restrict __str,
			     __const char *__restrict __with,
			     unsigned int *__restrict __replace_count);

/* Returns the next entry in ARGZ & ARGZ_LEN after ENTRY, or NULL if there
   are no more. If entry is NULL, then the first entry is returned. This
   behavior allows two convenient iteration styles:

    char *entry = 0;
    while ((entry = argz_next (argz, argz_len, entry)))
      ...;

   or

    char *entry;
    for (entry = argz; entry; entry = argz_next (argz, argz_len, entry))
      ...;
*/
extern char *__argz_next (__const char *__restrict __argz, size_t __argz_len,
			  __const char *__restrict __entry);
extern char *argz_next (__const char *__restrict __argz, size_t __argz_len,
			__const char *__restrict __entry);

#endif /* argz.h */
