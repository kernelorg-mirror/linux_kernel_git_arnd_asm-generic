/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_POWERPC_SYSCALLS_H
#define __ASM_POWERPC_SYSCALLS_H
#ifdef __KERNEL__

#include <linux/compiler.h>
#include <linux/linkage.h>
#include <linux/types.h>
#include <linux/compat.h>

#include <asm/syscall.h>
#include <asm/unistd.h>
#include <asm/ucontext.h>

long sys_ni_syscall(void);

struct rtas_args;

/*
 * long long munging:
 * The 32 bit ABI passes long longs in an odd even register pair.
 * High and low parts are swapped depending on endian mode,
 * so define a macro (similar to mips linux32) to handle that.
 */
#ifdef __LITTLE_ENDIAN__
#define merge_64(low, high) (((u64)high << 32) | low)
#else
#define merge_64(high, low) (((u64)high << 32) | low)
#endif

/*
 * PowerPC architecture-specific syscalls
 */

long sys_rtas(struct rtas_args __user *uargs);

#ifdef CONFIG_PPC64
long sys_ppc64_personality(unsigned long personality);
asmlinkage long sys_ppc64_sync_file_range2(int fd, unsigned int flags,
					   loff_t offset, loff_t nbytes);

#ifdef CONFIG_COMPAT
long compat_sys_ppc64_personality(unsigned long personality);
#endif /* CONFIG_COMPAT */
#endif /* CONFIG_PPC64 */

long sys_swapcontext(struct ucontext __user *old_ctx,
		     struct ucontext __user *new_ctx, long ctx_size);
long sys_mmap(unsigned long addr, size_t len,
	      unsigned long prot, unsigned long flags,
	      unsigned long fd, off_t offset);
long sys_mmap2(unsigned long addr, size_t len,
	       unsigned long prot, unsigned long flags,
	       unsigned long fd, unsigned long pgoff);
long sys_switch_endian(void);

#ifdef CONFIG_PPC32
long sys_debug_setcontext(struct ucontext __user *ctx, int ndbg,
			  struct sig_dbg_op __user *dbg);
#endif

long sys_subpage_prot(unsigned long addr,
		      unsigned long len, u32 __user *map);

#ifdef CONFIG_COMPAT
struct ucontext32;
long compat_sys_swapcontext(struct ucontext32 __user *old_ctx,
			    struct ucontext32 __user *new_ctx,
			    int ctx_size);
long compat_sys_old_getrlimit(unsigned int resource,
			      struct compat_rlimit __user *rlim);
#endif /* CONFIG_COMPAT */

/*
 * Architecture specific signatures required by long long munging:
 * The 32 bit ABI passes long longs in an odd even register pair.
 * The following signatures provide a machine long parameter for
 * each register that will be supplied. The implementation is
 * responsible for combining parameter pairs.
 */

#ifdef CONFIG_COMPAT
long compat_sys_mmap2(unsigned long addr, size_t len,
		      unsigned long prot, unsigned long flags,
		      unsigned long fd, unsigned long pgoff);
#endif /* CONFIG_COMPAT */

#else

#define __SYSCALL_WITH_COMPAT(nr, native, compat)	__SYSCALL(nr, native)
#define __SYSCALL(nr, entry) \
	long __powerpc_##entry(const struct pt_regs *regs);

#ifdef CONFIG_PPC64
#include <asm/syscall_table_64.h>
#else
#include <asm/syscall_table_32.h>
#endif /* CONFIG_PPC64 */

#endif /* __KERNEL__ */
#endif /* __ASM_POWERPC_SYSCALLS_H */
