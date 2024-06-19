// SPDX-License-Identifier: GPL-2.0-only
/*
 * arch/arm64/kernel/sys32.c
 *
 * Copyright (C) 2015 ARM Ltd.
 */

#include <linux/compat.h>
#include <linux/compiler.h>
#include <linux/syscalls.h>

#include <asm/syscall.h>
#include <asm/unistd_compat_32.h>

COMPAT_SYSCALL_DEFINE3(aarch32_statfs64, const char __user *, pathname,
		       compat_size_t, sz, struct compat_statfs64 __user *, buf)
{
	/*
	 * 32-bit ARM applies an OABI compatibility fixup to statfs64 and
	 * fstatfs64 regardless of whether OABI is in use, and therefore
	 * arbitrary binaries may rely upon it, so we must do the same.
	 * For more details, see commit:
	 *
	 * 713c481519f19df9 ("[ARM] 3108/2: old ABI compat: statfs64 and
	 * fstatfs64")
	 */
	if (sz == 88)
		sz = 84;

	return kcompat_sys_statfs64(pathname, sz, buf);
}

COMPAT_SYSCALL_DEFINE3(aarch32_fstatfs64, unsigned int, fd, compat_size_t, sz,
		       struct compat_statfs64 __user *, buf)
{
	/* see aarch32_statfs64 */
	if (sz == 88)
		sz = 84;

	return kcompat_sys_fstatfs64(fd, sz, buf);
}

/*
 * Note: off_4k is always in units of 4K. If we can't do the
 * requested offset because it is not page-aligned, we return -EINVAL.
 */
COMPAT_SYSCALL_DEFINE6(aarch32_mmap2, unsigned long, addr, unsigned long, len,
		       unsigned long, prot, unsigned long, flags,
		       unsigned long, fd, unsigned long, off_4k)
{
	if (off_4k & (~PAGE_MASK >> 12))
		return -EINVAL;

	off_4k >>= (PAGE_SHIFT - 12);

	return ksys_mmap_pgoff(addr, len, prot, flags, fd, off_4k);
}

#define __SYSCALL_WITH_COMPAT(nr, sym, compat) __SYSCALL(nr, compat)

#undef __SYSCALL
#define __SYSCALL(nr, sym)	asmlinkage long __arm64_##sym(const struct pt_regs *);
#include <asm/syscall_table_32.h>

#undef __SYSCALL
#define __SYSCALL(nr, sym)	[nr] = __arm64_##sym,

const syscall_fn_t compat_sys_call_table[__NR_compat32_syscalls] = {
	[0 ... __NR_compat32_syscalls - 1] = __arm64_sys_ni_syscall,
#include <asm/syscall_table_32.h>
};
