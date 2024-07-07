/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _ASM_MIPS_SYSCALLS_H
#define _ASM_MIPS_SYSCALLS_H

#include <linux/linkage.h>
#include <linux/compat.h>

/* mips is the only architecture with 7-argument system calls */
#undef SYSCALL_DEFINE_MAXARGS
#define SYSCALL_DEFINE_MAXARGS 7
#define __MAP7(m,t,a,...) m(t,a), __MAP6(m,__VA_ARGS__)
#define SYSCALL_DEFINE7(name, ...) SYSCALL_DEFINEx(7, _##name, __VA_ARGS__)

asmlinkage long sys_mips_pipe(void);
asmlinkage long mipsmt_sys_sched_setaffinity(pid_t pid, unsigned int len,
                                     unsigned long __user *user_mask_ptr);
asmlinkage long mipsmt_sys_sched_getaffinity(pid_t pid, unsigned int len,
                                     unsigned long __user *user_mask_ptr);
asmlinkage long sys_fadvise64_64_7(int fd, int __pad,
				   u32 a2, u32 a3,
				   u32 a4, u32 a5,
				   int flags);
asmlinkage long sys_sync_file_range7(int fd, int __pad,
				     u32 a2, u32 a3,
				     u32 a4, u32 a5,
				     unsigned int flags);
asmlinkage int sys32_sigsuspend(compat_sigset_t __user *uset);
asmlinkage long sys_n32_rt_sigreturn(void);

#endif
