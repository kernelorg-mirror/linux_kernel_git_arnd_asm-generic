/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_ARM64_SYSCALLS_H
#define __ASM_ARM64_SYSCALLS_H

#include <linux/compat.h>
#include <asm-generic/syscalls.h>

asmlinkage long sys_arm64_personality(unsigned int personality);

struct compat_statfs64;

asmlinkage long compat_sys_aarch32_statfs64(const char __user * pathname, compat_size_t sz, struct compat_statfs64 __user * buf);
asmlinkage long compat_sys_aarch32_fstatfs64(unsigned int fd, compat_size_t sz, struct compat_statfs64 __user * buf);
asmlinkage long compat_sys_aarch32_mmap2(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off_4k);

#endif
