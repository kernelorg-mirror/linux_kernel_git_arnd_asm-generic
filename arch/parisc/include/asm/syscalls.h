/* SPDX-License-Identifier: GPL-2.0-only */
#ifndef _ASM_PARISC_SYSCALLS_H
#define _ASM_PARISC_SYSCALLS_H

#include <linux/compat.h>
#include <asm-generic/syscalls.h>

asmlinkage long sys_parisc_personality(unsigned long personality);
asmlinkage long sys_parisc_timerfd_create(int clockid, int flags);
asmlinkage long sys_parisc_signalfd4(int ufd, sigset_t __user *user_mask, size_t sizemask, int flags);
asmlinkage long compat_sys_parisc_signalfd4(int ufd, compat_sigset_t __user *user_mask, compat_size_t sizemask, int flags);
asmlinkage long sys_parisc_eventfd2(unsigned int count, int flags);
asmlinkage long sys_parisc_userfaultfd(int flags);
asmlinkage long sys_parisc_pipe2(int __user *fildes, int flags);
asmlinkage long sys_parisc_inotify_init1(int flags);
asmlinkage notrace long sys_parisc_madvise(unsigned long start, size_t len_in, int behavior);

#endif
