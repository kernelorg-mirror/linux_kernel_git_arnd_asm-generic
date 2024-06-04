/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * syscalls.h - Linux syscall interfaces (arch-specific)
 *
 * Copyright (c) 2008 Jaswinder Singh Rajput
 */

#ifndef _ASM_X86_SYSCALLS_H
#define _ASM_X86_SYSCALLS_H

#include <asm-generic/syscalls.h>

/* Common in X86_32 and X86_64 */
/* kernel/ioport.c */
long ksys_ioperm(unsigned long from, unsigned long num, int turn_on);

asmlinkage long sys_get_thread_area(struct user_desc __user *u_info);
asmlinkage long sys_arch_prctl(int option, unsigned long arg2);
asmlinkage long sys_mmap(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off);
asmlinkage long sys_iopl(unsigned int level);
asmlinkage long sys_modify_ldt(int func, void __user *ptr , unsigned long bytecount);
asmlinkage long sys_set_thread_area(struct user_desc __user *u_info);
asmlinkage long sys_set_thread_area(struct user_desc __user *user_desc);

struct vm86_struct;
asmlinkage long sys_vm86old(struct vm86_struct __user * user_vm86);
asmlinkage long sys_vm86(unsigned long cmd, unsigned long arg);

asmlinkage long compat_sys_arch_prctl(int option, unsigned long arg2);
struct mmap_arg_struct32;

struct stat64;
asmlinkage long compat_sys_ia32_stat64(const char __user *filename, struct stat64 __user *statbuf);
asmlinkage long compat_sys_ia32_lstat64(const char __user *filename, struct stat64 __user *statbuf);
asmlinkage long compat_sys_ia32_fstat64(unsigned int fd, struct stat64 __user *statbuf);
asmlinkage long compat_sys_ia32_fstatat64(unsigned int dfd, const char __user *filename, struct stat64 __user *statbuf, int flag);
asmlinkage long compat_sys_ia32_mmap(struct mmap_arg_struct32 __user *arg);
asmlinkage long compat_sys_ia32_clone(unsigned long clone_flags, unsigned long newsp, int __user *parent_tidptr, unsigned long tls_val, int __user *child_tidptr);

/* Non-generic prototype for preadv2 and pwritev2 */
asmlinkage long compat_sys_x32_preadv64v2(unsigned long fd,
		const struct iovec __user *vec,
		unsigned long vlen, loff_t pos, rwf_t flags);
asmlinkage long compat_sys_x32_pwritev64v2(unsigned long fd,
		const struct iovec __user *vec,
		unsigned long vlen, loff_t pos, rwf_t flags);
asmlinkage long compat_sys_x32_rt_sigreturn(void);

struct compat_rlimit;
asmlinkage long compat_sys_old_getrlimit(unsigned int resource, struct compat_rlimit __user *rlim);

#endif /* _ASM_X86_SYSCALLS_H */
