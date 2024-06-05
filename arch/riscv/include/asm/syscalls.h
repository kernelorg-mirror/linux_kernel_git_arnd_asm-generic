/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_RISCV_SYSCALLS_H
#define __ASM_RISCV_SYSCALLS_H

#include <asm-generic/syscalls.h>

struct riscv_hwprobe;
asmlinkage long sys_riscv_hwprobe(struct riscv_hwprobe __user *pairs, size_t pair_count, size_t cpusetsize, unsigned long __user * cpus, unsigned int flags);
asmlinkage long sys_riscv_flush_icache(uintptr_t start, uintptr_t end, uintptr_t flags);

#endif
