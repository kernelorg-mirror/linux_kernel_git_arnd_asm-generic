/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_ARC_SYSCALLS_H
#define _ASM_ARC_SYSCALLS_H  1

#include <linux/compiler.h>
#include <linux/linkage.h>
#include <linux/types.h>

asmlinkage long sys_clone_wrapper(int, int, int, int, int);
asmlinkage long sys_clone3_wrapper(void *, size_t);
asmlinkage long sys_arc_settls(void *);
asmlinkage long sys_arc_gettls(void);
asmlinkage long sys_arc_usr_cmpxchg(int *, int, int);

#include <asm-generic/syscalls.h>

#endif
