/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _SYSTBLS_H
#define _SYSTBLS_H

#include <linux/kernel.h>
#include <linux/types.h>

struct pt_regs;

asmlinkage long sparc_fork(struct pt_regs *regs);
asmlinkage long sparc_vfork(struct pt_regs *regs);
asmlinkage long sparc_clone(struct pt_regs *regs);
asmlinkage void sparc64_set_context(struct pt_regs *regs);
asmlinkage void sparc64_get_context(struct pt_regs *regs);
asmlinkage void sparc_breakpoint(struct pt_regs *regs);
void do_rt_sigreturn(struct pt_regs *regs);

#endif /* _SYSTBLS_H */
