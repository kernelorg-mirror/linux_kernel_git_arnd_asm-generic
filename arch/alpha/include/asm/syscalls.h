/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_ALPHA_SYSCALLS_H
#define _ASM_ALPHA_SYSCALLS_H

#include <linux/posix_types.h>
#include <asm-generic/syscalls.h>

asmlinkage long sys_getdtablesize(void);
asmlinkage long sys_getxuid(void);
asmlinkage long sys_getxgid(void);
asmlinkage long sys_getxpid(void);
asmlinkage long sys_alpha_pipe(void);

asmlinkage long sys_osf_brk(unsigned long brk);
asmlinkage long sys_osf_set_program_attributes(unsigned long text_start, unsigned long text_len, unsigned long bss_start, unsigned long bss_len);
struct osf_dirent;
asmlinkage long sys_osf_getdirentries(unsigned int fd, struct osf_dirent __user *dirent, unsigned int count, long __user *basep);
asmlinkage long sys_osf_mmap(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off);
struct osf_statfs;
asmlinkage long sys_osf_statfs(const char __user *pathname, struct osf_statfs __user *buffer, unsigned long bufsiz);
struct osf_stat;
asmlinkage long sys_osf_stat(char __user *name, struct osf_stat __user *buf);
asmlinkage long sys_osf_lstat(char __user *name, struct osf_stat __user *buf);
asmlinkage long sys_osf_fstat(int fd, struct osf_stat __user *buf);
asmlinkage long sys_osf_fstatfs(unsigned long fd, struct osf_statfs __user *buffer, unsigned long bufsiz);
struct osf_statfs64;
asmlinkage long sys_osf_statfs64(char __user *pathname, struct osf_statfs64 __user *buffer, unsigned long bufsiz);
asmlinkage long sys_osf_fstatfs64(unsigned long fd, struct osf_statfs64 __user *buffer, unsigned long bufsiz);
asmlinkage long sys_osf_mount(unsigned long typenr, const char __user *path, int flag, void __user *data);
asmlinkage long sys_osf_utsname(char __user *name);
asmlinkage long sys_osf_getdomainname(char __user *name, int namelen);
enum pl_code;
union pl_args;
asmlinkage long sys_osf_proplist_syscall(enum pl_code code, union pl_args __user *args);
struct sigstack;
asmlinkage long sys_osf_sigstack(struct sigstack __user *uss, struct sigstack __user *uoss);
asmlinkage long sys_osf_sysinfo(int command, char __user *buf, long count);
asmlinkage long sys_osf_getsysinfo(unsigned long op, void __user *buffer, unsigned long nbytes, int __user *start, void __user *arg);
asmlinkage long sys_osf_setsysinfo(unsigned long op, void __user *buffer, unsigned long nbytes, int __user *start, void __user *arg);
struct timeval32;
struct timezone;
asmlinkage long sys_osf_gettimeofday(struct timeval32 __user *tv, struct timezone __user *tz);
asmlinkage long sys_osf_settimeofday(struct timeval32 __user *tv, struct timezone __user *tz);
asmlinkage long sys_osf_utimes(const char __user *filename, struct timeval32 __user *tvs);
asmlinkage long sys_osf_select(int n, fd_set __user *inp, fd_set __user *outp, fd_set __user *exp, struct timeval32 __user *tvp);
struct rusage32;
asmlinkage long sys_osf_getrusage(int who, struct rusage32 __user *ru);
asmlinkage long sys_osf_wait4(pid_t pid, int __user *ustatus, int options, struct rusage32 __user *ur);
asmlinkage long sys_osf_usleep_thread(struct timeval32 __user *sleep, struct timeval32 __user *remain);
asmlinkage long sys_osf_getpriority(int which, int who);
asmlinkage long sys_osf_sigprocmask(int how, unsigned long newmask);
asmlinkage long sys_osf_sigaction(int sig, const struct osf_sigaction __user *act, struct osf_sigaction __user *oact);
asmlinkage long sys_alpha_rt_sigaction(int sig, const struct sigaction __user *act, struct sigaction __user *oact, size_t sigsetsize, void __user *restorer);

struct timex32;
asmlinkage long sys_old_adjtimex(struct timex32 __user * txc_p);
asmlinkage long sys_sethae(unsigned long val);

#endif
