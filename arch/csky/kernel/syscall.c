// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microsystems co.,ltd.

#include <linux/syscalls.h>

SYSCALL_DEFINE1(set_thread_area, unsigned long, addr)
{
	struct thread_info *ti = task_thread_info(current);
	struct pt_regs *reg = current_pt_regs();

	reg->tls = addr;
	ti->tp_value = addr;

	return 0;
}

SYSCALL_DEFINE6(mmap2,
	unsigned long, addr,
	unsigned long, len,
	unsigned long, prot,
	unsigned long, flags,
	unsigned long, fd,
	unsigned long, offset)
{
	if (unlikely(offset & (~PAGE_MASK >> 12)))
		return -EINVAL;

	return ksys_mmap_pgoff(addr, len, prot, flags, fd,
			       offset >> (PAGE_SHIFT - 12));
}
