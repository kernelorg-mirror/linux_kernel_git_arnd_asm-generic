/* SPDX-License-Identifier: GPL-2.0-only */

#ifndef _ASM_UM_SYSCALLS_H
#define _ASM_UM_SYSCALLS_H

asmlinkage long sys_arch_prctl(int option, unsigned long arg2);
asmlinkage long sys_modify_ldt(int func, void __user *ptr , unsigned long bytecount);
asmlinkage long sys_set_thread_area(struct user_desc __user *user_desc);
asmlinkage long sys_get_thread_area(struct user_desc __user *user_desc);

#endif
