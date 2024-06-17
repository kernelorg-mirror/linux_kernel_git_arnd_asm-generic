/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * syscalls.h - Linux syscall interfaces (arch-specific)
 *
 * Copyright (c) 2008 Jaswinder Singh Rajput
 */

#ifndef _ASM_X86_SYSCALLS_H
#define _ASM_X86_SYSCALLS_H

/* Common in X86_32 and X86_64 */
/* kernel/ioport.c */
long ksys_ioperm(unsigned long from, unsigned long num, int turn_on);

/* Non-generic prototype for preadv2 and pwritev2 */
asmlinkage long compat_sys_x32_preadv64v2(unsigned long fd,
		const struct iovec __user *vec,
		unsigned long vlen, loff_t pos, rwf_t flags);
asmlinkage long compat_sys_x32_pwritev64v2(unsigned long fd,
		const struct iovec __user *vec,
		unsigned long vlen, loff_t pos, rwf_t flags);

#endif /* _ASM_X86_SYSCALLS_H */
