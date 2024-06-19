// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * sys_ppc32.c: 32-bit system calls with complex calling conventions.
 *
 * Copyright (C) 2001 IBM
 * Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 1997 David S. Miller (davem@caip.rutgers.edu)
 *
 * 32-bit system calls with 64-bit arguments pass those in register pairs.
 * This must be specially dealt with on 64-bit kernels. The compat_arg_u64_dual
 * in generic compat syscalls is not always usable because the register
 * pairing is constrained depending on preceding arguments.
 *
 * An analogous problem exists on 32-bit kernels with ARCH_HAS_SYSCALL_WRAPPER,
 * the defined system call functions take the pt_regs as an argument, and there
 * is a mapping macro which maps registers to arguments
 * (SC_POWERPC_REGS_TO_ARGS) which also does not deal with these 64-bit
 * arguments.
 *
 * This file contains these system calls.
 */

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/fs.h> 
#include <linux/mm.h> 
#include <linux/file.h> 
#include <linux/signal.h>
#include <linux/resource.h>
#include <linux/times.h>
#include <linux/smp.h>
#include <linux/sem.h>
#include <linux/msg.h>
#include <linux/shm.h>
#include <linux/poll.h>
#include <linux/personality.h>
#include <linux/stat.h>
#include <linux/in.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/sysctl.h>
#include <linux/binfmts.h>
#include <linux/security.h>
#include <linux/compat.h>
#include <linux/ptrace.h>
#include <linux/elf.h>
#include <linux/ipc.h>
#include <linux/slab.h>

#include <asm/ptrace.h>
#include <asm/types.h>
#include <linux/uaccess.h>
#include <asm/unistd.h>
#include <asm/time.h>
#include <asm/mmu_context.h>
#include <asm/ppc-pci.h>
#include <asm/syscalls.h>
#include <asm/switch_to.h>

#ifdef CONFIG_PPC32
#define PPC32_SYSCALL_DEFINE4	SYSCALL_DEFINE4
#define PPC32_SYSCALL_DEFINE5	SYSCALL_DEFINE5
#define PPC32_SYSCALL_DEFINE6	SYSCALL_DEFINE6
#else
#define PPC32_SYSCALL_DEFINE4	COMPAT_SYSCALL_DEFINE4
#define PPC32_SYSCALL_DEFINE5	COMPAT_SYSCALL_DEFINE5
#define PPC32_SYSCALL_DEFINE6	COMPAT_SYSCALL_DEFINE6
#endif
