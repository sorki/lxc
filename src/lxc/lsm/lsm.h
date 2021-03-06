/*
 * lxc: linux Container library
 *
 * Copyright © 2013 Oracle.
 *
 * Authors:
 * Dwight Engen <dwight.engen@oracle.com>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __LXC_LSM_H
#define __LXC_LSM_H

struct lxc_conf;

#include <sys/types.h>

#include "../utils.h"

#define LXC_LSMATTRLEN (5 + (LXC_NUMSTRLEN64) + 7 + 1)

struct lsm_drv {
	const char *name;

	int (*enabled)(void);
	char *(*process_label_get)(pid_t pid);
	int (*process_label_set)(const char *label, struct lxc_conf *conf,
				 bool use_default, bool on_exec);
};

#if HAVE_APPARMOR || HAVE_SELINUX
extern void lsm_init(void);
extern int lsm_enabled(void);
extern const char *lsm_name(void);
extern char *lsm_process_label_get(pid_t pid);
extern int lsm_process_label_set(const char *label, struct lxc_conf *conf,
				 bool use_default, bool on_exec);
extern int lsm_process_label_fd_get(pid_t pid, bool on_exec);
extern int lsm_process_label_set_at(int label_fd, const char *label,
				    bool on_exec);
#else
static inline void lsm_init(void)
{
	return;
}

static inline int lsm_enabled(void) {
	return 0;
}

static inline const char *lsm_name(void)
{
	return "none";
}

static inline char *lsm_process_label_get(pid_t pid)
{
	return NULL;
}

static inline int lsm_process_label_set(const char *label,
					struct lxc_conf *conf, bool use_default,
					bool on_exec)
{
	return 0;
}

static inline int lsm_process_label_fd_get(pid_t pid, bool on_exec)
{
	return 0;
}

extern int lsm_process_label_set_at(int label_fd, const char *label,
				    bool on_exec)
{
	return 0;
}
#endif

#endif
