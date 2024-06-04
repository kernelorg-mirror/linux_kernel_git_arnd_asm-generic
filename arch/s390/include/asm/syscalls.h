/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_S390_SYSCALLS_H
#define _ASM_S390_SYSCALLS_H

struct gs_cb;

asmlinkage long sys_s390_personality(unsigned int personality);
asmlinkage long sys_s390_runtime_instr(int command, int signum);
asmlinkage long sys_s390_guarded_storage(int command, struct gs_cb __user *);
asmlinkage long sys_s390_pci_mmio_write(unsigned long, const void __user *, size_t);
asmlinkage long sys_s390_pci_mmio_read(unsigned long, void __user *, size_t);
asmlinkage long sys_s390_sthyi(unsigned long function_code, void __user *buffer, u64 __user *return_code, unsigned long flags);
asmlinkage long sys_s390_ipc(uint call, int first, unsigned long second, unsigned long third, void __user *ptr);
asmlinkage long sys_s390_guarded_storage(int command, struct gs_cb __user *gs_cb);
asmlinkage long sys_s390_runtime_instr(int command, int signum);

#ifdef CONFIG_COMPAT
#include <linux/compat.h>

struct stat64_emu31;
struct mmap_arg_struct_emu31;
struct fadvise64_64_args;

asmlinkage long compat_sys_s390_stat64(const char __user *filename, struct stat64_emu31 __user *statbuf);
asmlinkage long compat_sys_s390_lstat64(const char __user *filename, struct stat64_emu31 __user *statbuf);
asmlinkage long compat_sys_s390_fstat64(unsigned int fd, struct stat64_emu31 __user *statbuf);
asmlinkage long compat_sys_s390_fstatat64(unsigned int dfd, const char __user *filename, struct stat64_emu31 __user *statbuf, int flag);
asmlinkage long compat_sys_s390_old_mmap(struct mmap_arg_struct_emu31 __user *arg);
asmlinkage long compat_sys_s390_mmap2(struct mmap_arg_struct_emu31 __user *arg);
asmlinkage long compat_sys_s390_read(unsigned int fd, char __user *buf, compat_size_t count);
asmlinkage long compat_sys_s390_write(unsigned int fd, const char __user *buf, compat_size_t count);
asmlinkage long compat_sys_s390_fadvise64(int fd, u32 high, u32 low, compat_size_t len, int advise);
asmlinkage long compat_sys_s390_fadvise64_64(struct fadvise64_64_args __user *args);
asmlinkage long compat_sys_s390_fallocate(int fd, int mode, u32 offhigh, u32 offlow, u32 lenhigh, u32 lenlow);
asmlinkage long compat_sys_s390_ipc(uint call, int first, compat_ulong_t second, compat_ulong_t third, compat_uptr_t ptr);
#endif

#endif
