/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _SPARC64_SYSCALLS_H
#define _SPARC64_SYSCALLS_H

#include <linux/compat.h>
#include <asm/utrap.h>

asmlinkage long sys_sparc_pipe(void);
asmlinkage long sys_nis_syscall(void);
asmlinkage long sys_getdomainname(char __user *name, int len);
asmlinkage long sys_mmap(unsigned long addr, unsigned long len,
			 unsigned long prot, unsigned long flags,
			 unsigned long fd, unsigned long off);
asmlinkage long sys_sparc_rt_sigaction(int sig,
                        const struct sigaction __user *act,
                        struct sigaction __user *oact,
                        void __user *restorer,
                        size_t sigsetsize);

#ifdef CONFIG_SPARC32
asmlinkage long sys_mmap2(unsigned long addr, unsigned long len,
			  unsigned long prot, unsigned long flags,
			  unsigned long fd, unsigned long pgoff);
asmlinkage long sys_sparc_remap_file_pages(unsigned long start, unsigned long size,
			    unsigned long prot, unsigned long pgoff,
			    unsigned long flags);
asmlinkage long sys_sparc_sigaction(int sig,
                        struct old_sigaction __user *act,
                        struct old_sigaction __user *oact);
#endif /* CONFIG_SPARC32 */

#ifdef CONFIG_SPARC64
asmlinkage long sys_sparc_ipc(unsigned int call, int first,
			      unsigned long second,
			      unsigned long third,
			      void __user *ptr, long fifth);
asmlinkage long sys_sparc64_personality(unsigned long personality);
asmlinkage long sys_64_munmap(unsigned long addr, size_t len);
asmlinkage long sys_64_mremap(unsigned long addr,
			      unsigned long old_len,
			      unsigned long new_len,
			      unsigned long flags,
			      unsigned long new_addr);
asmlinkage long sys_utrap_install(utrap_entry_t type,
				  utrap_handler_t new_p,
				  utrap_handler_t new_d,
				  utrap_handler_t __user *old_p,
				  utrap_handler_t __user *old_d);
asmlinkage long sys_memory_ordering(unsigned long model);
struct compat_stat64;
asmlinkage long compat_sys_stat64(const char __user * filename,
				  struct compat_stat64 __user *statbuf);
asmlinkage long compat_sys_lstat64(const char __user * filename,
				   struct compat_stat64 __user *statbuf);
asmlinkage long compat_sys_fstat64(unsigned int fd,
				   struct compat_stat64 __user * statbuf);
asmlinkage long compat_sys_fstatat64(unsigned int dfd,
				     const char __user *filename,
				     struct compat_stat64 __user * statbuf, int flag);
asmlinkage long compat_sys_fallocate(int fd, int mode, u32 offhi, u32 offlo,
				     u32 lenhi, u32 lenlo);
asmlinkage long compat_sys_fstat64(unsigned int fd,
				   struct compat_stat64 __user * statbuf);
asmlinkage long compat_sys_fstatat64(unsigned int dfd,
				     const char __user *filename,
				     struct compat_stat64 __user * statbuf,
				     int flag);

asmlinkage long sys_sparc_adjtimex(struct __kernel_timex __user *txc_p);
asmlinkage long sys_sparc_clock_adjtime(clockid_t which_clock,
					struct __kernel_timex __user *txc_p);

asmlinkage long compat_sys_sparc_sigaction(int sig,
                        struct compat_old_sigaction __user *act,
                        struct compat_old_sigaction __user *oact);
asmlinkage long compat_sys_sparc_rt_sigaction(int sig,
                        struct compat_sigaction __user *act,
                        struct compat_sigaction __user *oact,
                        void __user *restorer,
                        compat_size_t sigsetsize);

#endif /* CONFIG_SPARC64 */

#endif /* _SPARC64_SYSCALLS_H */
