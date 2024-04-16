/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#include <asm/bitsperlong.h>

/*
 * This file contains the system call numbers, based on the
 * layout of the x86-64 architecture, which embeds the
 * pointer to the syscall in the table.
 *
 * As a basic principle, no duplication of functionality
 * should be added, e.g. we don't use lseek when llseek
 * is present. New architectures should use this file
 * and implement the less feature-full calls in user space.
 */

#ifndef __SYSCALL
#define __SYSCALL(x, y)
#endif

#ifndef __SC
#define __SC(_cond, _nr, _sys) __SYSCALL_ ## _cond (_nr, _sys)
#endif

#ifndef __SCC
#ifdef __SYSCALL_COMPAT
#define __SCC(_cond, _nr, _sys, _comp) __SC(_cond, _nr, _comp)
#else
#define __SCC(_cond, _nr, _sys, _comp) __SC(_cond, _nr, _sys)
#endif
#endif

#define __SYSCALL_common(x, y)		__SYSCALL(__NR_ ## x, y)

#if __BITS_PER_LONG == 32 || defined(__SYSCALL_COMPAT)
#define __SYSCALL_32(_nr, _sys)		__SYSCALL(__NR_ ## _nr, _sys)
#define __SYSCALL_64(_nr, _sys)
#else
#define __SYSCALL_32(_nr, _sys)
#define __SYSCALL_64(_nr, _sys)		__SYSCALL(__NR_ ## _nr, _sys)
#endif

#if defined(__ARCH_WANT_TIME32_SYSCALLS)
#define __SYSCALL_time32(_nr, _sys)	__SYSCALL_32(_nr, _sys)
#else
#define __SYSCALL_time32(_nr, _sys)
#endif

#ifdef __ARCH_WANT_RENAMEAT
#define __SYSCALL_renameat(_nr, _sys)	__SYSCALL(__NR_ ## _nr, _sys)
#else
#define __SYSCALL_renameat(_nr, _sys)
#endif

#ifdef __ARCH_WANT_STAT64
#define __SYSCALL_stat64(_nr, _sys)	__SYSCALL(__NR_ ## _nr, _sys)
#else
#define __SYSCALL_stat64(_nr, _sys)
#endif

#ifdef __ARCH_WANT_NEW_STAT
#define __SYSCALL_newstat(_nr, _sys)	__SYSCALL(__NR_ ## _nr, _sys)
#else
#define __SYSCALL_newstat(_nr, _sys)
#endif

#ifdef __ARCH_WANT_SET_GET_RLIMIT
#define __SYSCALL_rlimit(_nr, _sys)	__SYSCALL(__NR_ ## _nr, _sys)
#else
#define __SYSCALL_rlimit(_nr, _sys)
#endif

#ifndef __ARCH_NOMMU
#define __SYSCALL_mmu(_nr, _sys)	__SYSCALL(__NR_ ## _nr, _sys)
#else
#define __SYSCALL_mmu(_nr, _sys)
#endif

#ifdef __ARCH_WANT_MEMFD_SECRET
#define __SYSCALL_memfd_secret(_nr, _sys) __SYSCALL(__NR_ ## _nr, _sys)
#else
#define __SYSCALL_memfd_secret(_nr, _sys)
#endif

/*
 * 32 bit systems traditionally used different
 * syscalls for off_t and loff_t arguments, while
 * 64 bit systems only need the off_t version.
 * For new 32 bit platforms, there is no need to
 * implement the old 32 bit off_t syscalls, so
 * they take different names.
 * Here we map the numbers so that both versions
 * use the same syscall table layout.
 */
#if __BITS_PER_LONG == 64
#define __NR_fcntl __NR3264_fcntl
#define __NR_statfs __NR3264_statfs
#define __NR_fstatfs __NR3264_fstatfs
#define __NR_truncate __NR3264_truncate
#define __NR_ftruncate __NR3264_ftruncate
#define __NR_lseek __NR3264_lseek
#define __NR_sendfile __NR3264_sendfile
#define __NR_mmap __NR3264_mmap
#define __NR_fadvise64 __NR3264_fadvise64
#endif

#if __BITS_PER_LONG == 32 || defined(__SYSCALL_COMPAT)
#define __NR_fcntl64 __NR3264_fcntl
#define __NR_statfs64 __NR3264_statfs
#define __NR_fstatfs64 __NR3264_fstatfs
#define __NR_truncate64 __NR3264_truncate
#define __NR_ftruncate64 __NR3264_ftruncate
#define __NR_llseek __NR3264_lseek
#define __NR_sendfile64 __NR3264_sendfile
#define __NR_mmap2 __NR3264_mmap
#define __NR_fadvise64_64 __NR3264_fadvise64
#endif

#define __NR_io_setup 0
__SCC(common, io_setup, sys_io_setup, compat_sys_io_setup)
#define __NR_io_destroy 1
__SC(common, io_destroy, sys_io_destroy)
#define __NR_io_submit 2
__SCC(common, io_submit, sys_io_submit, compat_sys_io_submit)
#define __NR_io_cancel 3
__SC(common, io_cancel, sys_io_cancel)
#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_io_getevents 4
__SC(time32, io_getevents, sys_io_getevents_time32)
__SC(64, io_getevents, sys_io_getevents)
#endif

#define __NR_setxattr 5
__SC(common, setxattr, sys_setxattr)
#define __NR_lsetxattr 6
__SC(common, lsetxattr, sys_lsetxattr)
#define __NR_fsetxattr 7
__SC(common, fsetxattr, sys_fsetxattr)
#define __NR_getxattr 8
__SC(common, getxattr, sys_getxattr)
#define __NR_lgetxattr 9
__SC(common, lgetxattr, sys_lgetxattr)
#define __NR_fgetxattr 10
__SC(common, fgetxattr, sys_fgetxattr)
#define __NR_listxattr 11
__SC(common, listxattr, sys_listxattr)
#define __NR_llistxattr 12
__SC(common, llistxattr, sys_llistxattr)
#define __NR_flistxattr 13
__SC(common, flistxattr, sys_flistxattr)
#define __NR_removexattr 14
__SC(common, removexattr, sys_removexattr)
#define __NR_lremovexattr 15
__SC(common, lremovexattr, sys_lremovexattr)
#define __NR_fremovexattr 16
__SC(common, fremovexattr, sys_fremovexattr)
#define __NR_getcwd 17
__SC(common, getcwd, sys_getcwd)
#define __NR_lookup_dcookie 18
__SC(common, lookup_dcookie, sys_ni_syscall)
#define __NR_eventfd2 19
__SC(common, eventfd2, sys_eventfd2)
#define __NR_epoll_create1 20
__SC(common, epoll_create1, sys_epoll_create1)
#define __NR_epoll_ctl 21
__SC(common, epoll_ctl, sys_epoll_ctl)
#define __NR_epoll_pwait 22
__SCC(common, epoll_pwait, sys_epoll_pwait, compat_sys_epoll_pwait)
#define __NR_dup 23
__SC(common, dup, sys_dup)
#define __NR_dup3 24
__SC(common, dup3, sys_dup3)
#define __NR3264_fcntl 25
__SCC(32, fcntl64, sys_fcntl64, compat_sys_fcntl64)
__SC(64, fcntl, sys_fcntl)

#define __NR_inotify_init1 26
__SC(common, inotify_init1, sys_inotify_init1)
#define __NR_inotify_add_watch 27
__SC(common, inotify_add_watch, sys_inotify_add_watch)
#define __NR_inotify_rm_watch 28
__SC(common, inotify_rm_watch, sys_inotify_rm_watch)
#define __NR_ioctl 29
__SCC(common, ioctl, sys_ioctl, compat_sys_ioctl)
#define __NR_ioprio_set 30
__SC(common, ioprio_set, sys_ioprio_set)
#define __NR_ioprio_get 31
__SC(common, ioprio_get, sys_ioprio_get)
#define __NR_flock 32
__SC(common, flock, sys_flock)
#define __NR_mknodat 33
__SC(common, mknodat, sys_mknodat)
#define __NR_mkdirat 34
__SC(common, mkdirat, sys_mkdirat)
#define __NR_unlinkat 35
__SC(common, unlinkat, sys_unlinkat)
#define __NR_symlinkat 36
__SC(common, symlinkat, sys_symlinkat)
#define __NR_linkat 37
__SC(common, linkat, sys_linkat)

#ifdef __ARCH_WANT_RENAMEAT
/* renameat is superseded with flags by renameat2 */
#define __NR_renameat 38
__SC(renameat, renameat, sys_renameat)
#endif /* __ARCH_WANT_RENAMEAT */

#define __NR_umount2 39
__SC(common, umount2, sys_umount)
#define __NR_mount 40
__SC(common, mount, sys_mount)
#define __NR_pivot_root 41
__SC(common, pivot_root, sys_pivot_root)
#define __NR3264_statfs 43
__SCC(32, statfs64, sys_statfs64, compat_sys_statfs64)
__SC(64, statfs, sys_statfs)
#define __NR3264_fstatfs 44
__SCC(32, fstatfs64, sys_fstatfs64, compat_sys_fstatfs64)
__SC(64, fstatfs, sys_fstatfs)
#define __NR3264_truncate 45
__SCC(32, truncate64, sys_truncate64, compat_sys_truncate64)
__SC(64, truncate, sys_truncate)
#define __NR3264_ftruncate 46
__SCC(32, ftruncate64, sys_ftruncate64, compat_sys_ftruncate64)
__SC(64, ftruncate, sys_ftruncate)
#define __NR_fallocate 47
__SCC(common, fallocate, sys_fallocate, compat_sys_fallocate)
#define __NR_faccessat 48
__SC(common, faccessat, sys_faccessat)
#define __NR_chdir 49
__SC(common, chdir, sys_chdir)
#define __NR_fchdir 50
__SC(common, fchdir, sys_fchdir)
#define __NR_chroot 51
__SC(common, chroot, sys_chroot)
#define __NR_fchmod 52
__SC(common, fchmod, sys_fchmod)
#define __NR_fchmodat 53
__SC(common, fchmodat, sys_fchmodat)
#define __NR_fchownat 54
__SC(common, fchownat, sys_fchownat)
#define __NR_fchown 55
__SC(common, fchown, sys_fchown)
#define __NR_openat 56
__SC(common, openat, sys_openat)
#define __NR_close 57
__SC(common, close, sys_close)
#define __NR_vhangup 58
__SC(common, vhangup, sys_vhangup)
#define __NR_pipe2 59
__SC(common, pipe2, sys_pipe2)
#define __NR_quotactl 60
__SC(common, quotactl, sys_quotactl)
#define __NR_getdents64 61
__SC(common, getdents64, sys_getdents64)
#define __NR3264_lseek 62
__SC(32, llseek, sys_llseek)
__SC(64, lseek, sys_lseek)
#define __NR_read 63
__SC(common, read, sys_read)
#define __NR_write 64
__SC(common, write, sys_write)
#define __NR_readv 65
__SCC(common, readv, sys_readv, sys_readv)
#define __NR_writev 66
__SCC(common, writev, sys_writev, sys_writev)
#define __NR_pread64 67
__SCC(common, pread64, sys_pread64, compat_sys_pread64)
#define __NR_pwrite64 68
__SCC(common, pwrite64, sys_pwrite64, compat_sys_pwrite64)
#define __NR_preadv 69
__SCC(common, preadv, sys_preadv, compat_sys_preadv)
#define __NR_pwritev 70
__SCC(common, pwritev, sys_pwritev, compat_sys_pwritev)
#define __NR3264_sendfile 71
__SC(32, sendfile64, sys_sendfile64)
__SC(64, sendfile, sys_sendfile64)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_pselect6 72
__SCC(time32, pselect6, sys_pselect6_time32, compat_sys_pselect6_time32)
__SC(64, pselect6, sys_pselect6)
#define __NR_ppoll 73
__SCC(time32, ppoll, sys_ppoll_time32, compat_sys_ppoll_time32)
__SC(64, ppoll, sys_ppoll)
#endif

#define __NR_signalfd4 74
__SCC(common, signalfd4, sys_signalfd4, compat_sys_signalfd4)
#define __NR_vmsplice 75
__SC(common, vmsplice, sys_vmsplice)
#define __NR_splice 76
__SC(common, splice, sys_splice)
#define __NR_tee 77
__SC(common, tee, sys_tee)
#define __NR_readlinkat 78
__SC(common, readlinkat, sys_readlinkat)

#ifdef __ARCH_WANT_STAT64
#define __NR_fstatat64 79
__SC(stat64, fstatat64, sys_fstatat64)
#endif

#ifdef __ARCH_WANT_NEW_STAT
#define __NR_fstatat 79
__SC(newstat, fstatat, sys_newfstatat)
#endif

#if defined(__ARCH_WANT_STAT64) || defined(__GEN_SYSCALL_TBL)
#define __NR_fstat64 80
__SC(stat64, fstat64, sys_fstat64)
#endif

#if defined(__ARCH_WANT_NEW_STAT) || defined(__GEN_SYSCALL_TBL)
#define __NR_fstat 80
__SC(newstat, fstat, sys_newfstat)
#endif

#define __NR_sync 81
__SC(common, sync, sys_sync)
#define __NR_fsync 82
__SC(common, fsync, sys_fsync)
#define __NR_fdatasync 83
__SC(common, fdatasync, sys_fdatasync)
#define __NR_sync_file_range 84
__SCC(common, sync_file_range, sys_sync_file_range, \
	  compat_sys_sync_file_range)

#define __NR_timerfd_create 85
__SC(common, timerfd_create, sys_timerfd_create)
#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_timerfd_settime 86
__SC(time32, timerfd_settime, sys_timerfd_settime32)
__SC(64, timerfd_settime, sys_timerfd_settime)
#define __NR_timerfd_gettime 87
__SC(time32, timerfd_gettime, sys_timerfd_gettime32)
__SC(64, timerfd_gettime, sys_timerfd_gettime)
#endif

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_utimensat 88
__SC(time32, utimensat, sys_utimensat_time32)
__SC(64, utimensat, sys_utimensat)
#endif

#define __NR_acct 89
__SC(common, acct, sys_acct)
#define __NR_capget 90
__SC(common, capget, sys_capget)
#define __NR_capset 91
__SC(common, capset, sys_capset)
#define __NR_personality 92
__SC(common, personality, sys_personality)
#define __NR_exit 93
__SC(common, exit, sys_exit)
#define __NR_exit_group 94
__SC(common, exit_group, sys_exit_group)
#define __NR_waitid 95
__SCC(common, waitid, sys_waitid, compat_sys_waitid)
#define __NR_set_tid_address 96
__SC(common, set_tid_address, sys_set_tid_address)
#define __NR_unshare 97
__SC(common, unshare, sys_unshare)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_futex 98
__SC(time32, futex, sys_futex_time32)
__SC(64, futex, sys_futex)
#endif

#define __NR_set_robust_list 99
__SCC(common, set_robust_list, sys_set_robust_list, \
	  compat_sys_set_robust_list)
#define __NR_get_robust_list 100
__SCC(common, get_robust_list, sys_get_robust_list, \
	  compat_sys_get_robust_list)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_nanosleep 101
__SC(time32, nanosleep, sys_nanosleep_time32)
__SC(64, nanosleep, sys_nanosleep)
#endif

#define __NR_getitimer 102
__SCC(common, getitimer, sys_getitimer, compat_sys_getitimer)
#define __NR_setitimer 103
__SCC(common, setitimer, sys_setitimer, compat_sys_setitimer)
#define __NR_kexec_load 104
__SCC(common, kexec_load, sys_kexec_load, compat_sys_kexec_load)
#define __NR_init_module 105
__SC(common, init_module, sys_init_module)
#define __NR_delete_module 106
__SC(common, delete_module, sys_delete_module)
#define __NR_timer_create 107
__SCC(common, timer_create, sys_timer_create, compat_sys_timer_create)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_timer_gettime 108
__SC(time32, timer_gettime, sys_timer_gettime32)
__SC(64, timer_gettime, sys_timer_gettime)
#endif

#define __NR_timer_getoverrun 109
__SC(common, timer_getoverrun, sys_timer_getoverrun)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_timer_settime 110
__SC(time32, timer_settime, sys_timer_settime32)
__SC(64, timer_settime, sys_timer_settime)
#endif

#define __NR_timer_delete 111
__SC(common, timer_delete, sys_timer_delete)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_clock_settime 112
__SC(time32, clock_settime, sys_clock_settime32)
__SC(64, clock_settime, sys_clock_settime)
#define __NR_clock_gettime 113
__SC(time32, clock_gettime, sys_clock_gettime32)
__SC(64, clock_gettime, sys_clock_gettime)
#define __NR_clock_getres 114
__SC(time32, clock_getres, sys_clock_getres_time32)
__SC(64, clock_getres, sys_clock_getres)
#define __NR_clock_nanosleep 115
__SC(time32, clock_nanosleep, sys_clock_nanosleep_time32)
__SC(64, clock_nanosleep, sys_clock_nanosleep)
#endif

#define __NR_syslog 116
__SC(common, syslog, sys_syslog)
#define __NR_ptrace 117
__SCC(common, ptrace, sys_ptrace, compat_sys_ptrace)
#define __NR_sched_setparam 118
__SC(common, sched_setparam, sys_sched_setparam)
#define __NR_sched_setscheduler 119
__SC(common, sched_setscheduler, sys_sched_setscheduler)
#define __NR_sched_getscheduler 120
__SC(common, sched_getscheduler, sys_sched_getscheduler)
#define __NR_sched_getparam 121
__SC(common, sched_getparam, sys_sched_getparam)
#define __NR_sched_setaffinity 122
__SCC(common, sched_setaffinity, sys_sched_setaffinity, \
	  compat_sys_sched_setaffinity)
#define __NR_sched_getaffinity 123
__SCC(common, sched_getaffinity, sys_sched_getaffinity, \
	  compat_sys_sched_getaffinity)
#define __NR_sched_yield 124
__SC(common, sched_yield, sys_sched_yield)
#define __NR_sched_get_priority_max 125
__SC(common, sched_get_priority_max, sys_sched_get_priority_max)
#define __NR_sched_get_priority_min 126
__SC(common, sched_get_priority_min, sys_sched_get_priority_min)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_sched_rr_get_interval 127
__SC(time32, sched_rr_get_interval, sys_sched_rr_get_interval_time32)
__SC(64, sched_rr_get_interval, sys_sched_rr_get_interval)
#endif

#define __NR_restart_syscall 128
__SC(common, restart_syscall, sys_restart_syscall)
#define __NR_kill 129
__SC(common, kill, sys_kill)
#define __NR_tkill 130
__SC(common, tkill, sys_tkill)
#define __NR_tgkill 131
__SC(common, tgkill, sys_tgkill)
#define __NR_sigaltstack 132
__SCC(common, sigaltstack, sys_sigaltstack, compat_sys_sigaltstack)
#define __NR_rt_sigsuspend 133
__SCC(common, rt_sigsuspend, sys_rt_sigsuspend, compat_sys_rt_sigsuspend)
#define __NR_rt_sigaction 134
__SCC(common, rt_sigaction, sys_rt_sigaction, compat_sys_rt_sigaction)
#define __NR_rt_sigprocmask 135
__SCC(common, rt_sigprocmask, sys_rt_sigprocmask, compat_sys_rt_sigprocmask)
#define __NR_rt_sigpending 136
__SCC(common, rt_sigpending, sys_rt_sigpending, compat_sys_rt_sigpending)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_rt_sigtimedwait 137
__SCC(time32, rt_sigtimedwait, sys_rt_sigtimedwait_time32, compat_sys_rt_sigtimedwait_time32)
__SC(64, rt_sigtimedwait, sys_rt_sigtimedwait)
#endif

#define __NR_rt_sigqueueinfo 138
__SCC(common, rt_sigqueueinfo, sys_rt_sigqueueinfo, \
	  compat_sys_rt_sigqueueinfo)
#define __NR_rt_sigreturn 139
__SCC(common, rt_sigreturn, sys_rt_sigreturn, compat_sys_rt_sigreturn)
#define __NR_setpriority 140
__SC(common, setpriority, sys_setpriority)
#define __NR_getpriority 141
__SC(common, getpriority, sys_getpriority)
#define __NR_reboot 142
__SC(common, reboot, sys_reboot)
#define __NR_setregid 143
__SC(common, setregid, sys_setregid)
#define __NR_setgid 144
__SC(common, setgid, sys_setgid)
#define __NR_setreuid 145
__SC(common, setreuid, sys_setreuid)
#define __NR_setuid 146
__SC(common, setuid, sys_setuid)
#define __NR_setresuid 147
__SC(common, setresuid, sys_setresuid)
#define __NR_getresuid 148
__SC(common, getresuid, sys_getresuid)
#define __NR_setresgid 149
__SC(common, setresgid, sys_setresgid)
#define __NR_getresgid 150
__SC(common, getresgid, sys_getresgid)
#define __NR_setfsuid 151
__SC(common, setfsuid, sys_setfsuid)
#define __NR_setfsgid 152
__SC(common, setfsgid, sys_setfsgid)
#define __NR_times 153
__SCC(common, times, sys_times, compat_sys_times)
#define __NR_setpgid 154
__SC(common, setpgid, sys_setpgid)
#define __NR_getpgid 155
__SC(common, getpgid, sys_getpgid)
#define __NR_getsid 156
__SC(common, getsid, sys_getsid)
#define __NR_setsid 157
__SC(common, setsid, sys_setsid)
#define __NR_getgroups 158
__SC(common, getgroups, sys_getgroups)
#define __NR_setgroups 159
__SC(common, setgroups, sys_setgroups)
#define __NR_uname 160
__SC(common, uname, sys_newuname)
#define __NR_sethostname 161
__SC(common, sethostname, sys_sethostname)
#define __NR_setdomainname 162
__SC(common, setdomainname, sys_setdomainname)

#ifdef __ARCH_WANT_SET_GET_RLIMIT
/* getrlimit and setrlimit are superseded with prlimit64 */
#define __NR_getrlimit 163
__SCC(rlimit, getrlimit, sys_getrlimit, compat_sys_getrlimit)
#define __NR_setrlimit 164
__SCC(rlimit, setrlimit, sys_setrlimit, compat_sys_setrlimit)
#endif

#define __NR_getrusage 165
__SCC(common, getrusage, sys_getrusage, compat_sys_getrusage)
#define __NR_umask 166
__SC(common, umask, sys_umask)
#define __NR_prctl 167
__SC(common, prctl, sys_prctl)
#define __NR_getcpu 168
__SC(common, getcpu, sys_getcpu)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_gettimeofday 169
__SCC(time32, gettimeofday, sys_gettimeofday, compat_sys_gettimeofday)
__SC(64, gettimeofday, sys_gettimeofday)
#define __NR_settimeofday 170
__SCC(time32, settimeofday, sys_settimeofday, compat_sys_settimeofday)
__SC(64, settimeofday, sys_settimeofday)
#define __NR_adjtimex 171
__SC(time32, adjtimex, sys_adjtimex_time32)
__SC(64, adjtimex, sys_adjtimex)
#endif

#define __NR_getpid 172
__SC(common, getpid, sys_getpid)
#define __NR_getppid 173
__SC(common, getppid, sys_getppid)
#define __NR_getuid 174
__SC(common, getuid, sys_getuid)
#define __NR_geteuid 175
__SC(common, geteuid, sys_geteuid)
#define __NR_getgid 176
__SC(common, getgid, sys_getgid)
#define __NR_getegid 177
__SC(common, getegid, sys_getegid)
#define __NR_gettid 178
__SC(common, gettid, sys_gettid)
#define __NR_sysinfo 179
__SCC(common, sysinfo, sys_sysinfo, compat_sys_sysinfo)
#define __NR_mq_open 180
__SCC(common, mq_open, sys_mq_open, compat_sys_mq_open)
#define __NR_mq_unlink 181
__SC(common, mq_unlink, sys_mq_unlink)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_mq_timedsend 182
__SC(time32, mq_timedsend, sys_mq_timedsend_time32)
__SC(64, mq_timedsend, sys_mq_timedsend)
#define __NR_mq_timedreceive 183
__SC(time32, mq_timedreceive, sys_mq_timedreceive_time32)
__SC(64, mq_timedreceive, sys_mq_timedreceive)
#endif

#define __NR_mq_notify 184
__SCC(common, mq_notify, sys_mq_notify, compat_sys_mq_notify)
#define __NR_mq_getsetattr 185
__SCC(common, mq_getsetattr, sys_mq_getsetattr, compat_sys_mq_getsetattr)
#define __NR_msgget 186
__SC(common, msgget, sys_msgget)
#define __NR_msgctl 187
__SCC(common, msgctl, sys_msgctl, compat_sys_msgctl)
#define __NR_msgrcv 188
__SCC(common, msgrcv, sys_msgrcv, compat_sys_msgrcv)
#define __NR_msgsnd 189
__SCC(common, msgsnd, sys_msgsnd, compat_sys_msgsnd)
#define __NR_semget 190
__SC(common, semget, sys_semget)
#define __NR_semctl 191
__SCC(common, semctl, sys_semctl, compat_sys_semctl)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_semtimedop 192
__SC(time32, semtimedop, sys_semtimedop_time32)
__SC(64, semtimedop, sys_semtimedop)
#endif

#define __NR_semop 193
__SC(common, semop, sys_semop)
#define __NR_shmget 194
__SC(common, shmget, sys_shmget)
#define __NR_shmctl 195
__SCC(common, shmctl, sys_shmctl, compat_sys_shmctl)
#define __NR_shmat 196
__SCC(common, shmat, sys_shmat, compat_sys_shmat)
#define __NR_shmdt 197
__SC(common, shmdt, sys_shmdt)
#define __NR_socket 198
__SC(common, socket, sys_socket)
#define __NR_socketpair 199
__SC(common, socketpair, sys_socketpair)
#define __NR_bind 200
__SC(common, bind, sys_bind)
#define __NR_listen 201
__SC(common, listen, sys_listen)
#define __NR_accept 202
__SC(common, accept, sys_accept)
#define __NR_connect 203
__SC(common, connect, sys_connect)
#define __NR_getsockname 204
__SC(common, getsockname, sys_getsockname)
#define __NR_getpeername 205
__SC(common, getpeername, sys_getpeername)
#define __NR_sendto 206
__SC(common, sendto, sys_sendto)
#define __NR_recvfrom 207
__SCC(common, recvfrom, sys_recvfrom, compat_sys_recvfrom)
#define __NR_setsockopt 208
__SCC(common, setsockopt, sys_setsockopt, sys_setsockopt)
#define __NR_getsockopt 209
__SCC(common, getsockopt, sys_getsockopt, sys_getsockopt)
#define __NR_shutdown 210
__SC(common, shutdown, sys_shutdown)
#define __NR_sendmsg 211
__SCC(common, sendmsg, sys_sendmsg, compat_sys_sendmsg)
#define __NR_recvmsg 212
__SCC(common, recvmsg, sys_recvmsg, compat_sys_recvmsg)
#define __NR_readahead 213
__SCC(common, readahead, sys_readahead, compat_sys_readahead)
#define __NR_brk 214
__SC(common, brk, sys_brk)
#define __NR_munmap 215
__SC(common, munmap, sys_munmap)
#define __NR_mremap 216
__SC(common, mremap, sys_mremap)
#define __NR_add_key 217
__SC(common, add_key, sys_add_key)
#define __NR_request_key 218
__SC(common, request_key, sys_request_key)
#define __NR_keyctl 219
__SCC(common, keyctl, sys_keyctl, compat_sys_keyctl)
#define __NR_clone 220
__SC(common, clone, sys_clone)
#define __NR_execve 221
__SCC(common, execve, sys_execve, compat_sys_execve)
#define __NR3264_mmap 222
__SC(32, mmap2, sys_mmap2)
__SC(64, mmap, sys_mmap)
#define __NR3264_fadvise64 223
__SCC(32, fadvise64_64, sys_fadvise64_64, compat_sys_fadvise64_64)
__SC(64, fadvise64, sys_fadvise64_64)

/* CONFIG_MMU only */
#define __NR_swapon 224
__SC(common, swapon, sys_swapon)
#define __NR_swapoff 225
__SC(common, swapoff, sys_swapoff)
#define __NR_mprotect 226
__SC(common, mprotect, sys_mprotect)
#define __NR_msync 227
__SC(common, msync, sys_msync)
#define __NR_mlock 228
__SC(common, mlock, sys_mlock)
#define __NR_munlock 229
__SC(common, munlock, sys_munlock)
#define __NR_mlockall 230
__SC(common, mlockall, sys_mlockall)
#define __NR_munlockall 231
__SC(common, munlockall, sys_munlockall)
#define __NR_mincore 232
__SC(common, mincore, sys_mincore)
#define __NR_madvise 233
__SC(common, madvise, sys_madvise)
#define __NR_remap_file_pages 234
__SC(common, remap_file_pages, sys_remap_file_pages)
#define __NR_mbind 235
__SC(common, mbind, sys_mbind)
#define __NR_get_mempolicy 236
__SC(common, get_mempolicy, sys_get_mempolicy)
#define __NR_set_mempolicy 237
__SC(common, set_mempolicy, sys_set_mempolicy)
#define __NR_migrate_pages 238
__SC(common, migrate_pages, sys_migrate_pages)
#define __NR_move_pages 239
__SC(common, move_pages, sys_move_pages)

#define __NR_rt_tgsigqueueinfo 240
__SCC(common, rt_tgsigqueueinfo, sys_rt_tgsigqueueinfo, \
	  compat_sys_rt_tgsigqueueinfo)
#define __NR_perf_event_open 241
__SC(common, perf_event_open, sys_perf_event_open)
#define __NR_accept4 242
__SC(common, accept4, sys_accept4)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_recvmmsg 243
__SCC(time32, recvmmsg, sys_recvmmsg_time32, compat_sys_recvmmsg_time32)
__SC(64, recvmmsg, sys_recvmmsg)
#endif

/*
 * Architectures may provide up to 16 syscalls of their own
 * starting with this value.
 */
#define __NR_arch_specific_syscall 244

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_wait4 260
__SCC(time32, wait4, sys_wait4, compat_sys_wait4)
__SC(64, wait4, sys_wait4)
#endif

#define __NR_prlimit64 261
__SC(common, prlimit64, sys_prlimit64)
#define __NR_fanotify_init 262
__SC(common, fanotify_init, sys_fanotify_init)
#define __NR_fanotify_mark 263
__SC(common, fanotify_mark, sys_fanotify_mark)
#define __NR_name_to_handle_at         264
__SC(common, name_to_handle_at, sys_name_to_handle_at)
#define __NR_open_by_handle_at         265
__SC(common, open_by_handle_at, sys_open_by_handle_at)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_clock_adjtime 266
__SC(time32, clock_adjtime, sys_clock_adjtime32)
__SC(64, clock_adjtime, sys_clock_adjtime)
#endif

#define __NR_syncfs 267
__SC(common, syncfs, sys_syncfs)
#define __NR_setns 268
__SC(common, setns, sys_setns)
#define __NR_sendmmsg 269
__SCC(common, sendmmsg, sys_sendmmsg, compat_sys_sendmmsg)
#define __NR_process_vm_readv 270
__SC(common, process_vm_readv, sys_process_vm_readv)
#define __NR_process_vm_writev 271
__SC(common, process_vm_writev, sys_process_vm_writev)
#define __NR_kcmp 272
__SC(common, kcmp, sys_kcmp)
#define __NR_finit_module 273
__SC(common, finit_module, sys_finit_module)
#define __NR_sched_setattr 274
__SC(common, sched_setattr, sys_sched_setattr)
#define __NR_sched_getattr 275
__SC(common, sched_getattr, sys_sched_getattr)
#define __NR_renameat2 276
__SC(common, renameat2, sys_renameat2)
#define __NR_seccomp 277
__SC(common, seccomp, sys_seccomp)
#define __NR_getrandom 278
__SC(common, getrandom, sys_getrandom)
#define __NR_memfd_create 279
__SC(common, memfd_create, sys_memfd_create)
#define __NR_bpf 280
__SC(common, bpf, sys_bpf)
#define __NR_execveat 281
__SCC(common, execveat, sys_execveat, compat_sys_execveat)
#define __NR_userfaultfd 282
__SC(common, userfaultfd, sys_userfaultfd)
#define __NR_membarrier 283
__SC(common, membarrier, sys_membarrier)
#define __NR_mlock2 284
__SC(common, mlock2, sys_mlock2)
#define __NR_copy_file_range 285
__SC(common, copy_file_range, sys_copy_file_range)
#define __NR_preadv2 286
__SCC(common, preadv2, sys_preadv2, compat_sys_preadv2)
#define __NR_pwritev2 287
__SCC(common, pwritev2, sys_pwritev2, compat_sys_pwritev2)
#define __NR_pkey_mprotect 288
__SC(common, pkey_mprotect, sys_pkey_mprotect)
#define __NR_pkey_alloc 289
__SC(common, pkey_alloc,    sys_pkey_alloc)
#define __NR_pkey_free 290
__SC(common, pkey_free,     sys_pkey_free)
#define __NR_statx 291
__SC(common, statx,     sys_statx)

#if defined(__ARCH_WANT_TIME32_SYSCALLS) || __BITS_PER_LONG != 32
#define __NR_io_pgetevents 292
__SCC(time32, io_pgetevents, sys_io_pgetevents_time32, compat_sys_io_pgetevents)
__SC(64, io_pgetevents, sys_io_pgetevents)
#endif

#define __NR_rseq 293
__SC(common, rseq, sys_rseq)
#define __NR_kexec_file_load 294
__SC(common, kexec_file_load,     sys_kexec_file_load)

/* 295 through 402 are unassigned to sync up with generic numbers, don't use */

#if defined(__SYSCALL_COMPAT) || __BITS_PER_LONG == 32
#define __NR_clock_gettime64 403
__SC(32, clock_gettime64, sys_clock_gettime)
#define __NR_clock_settime64 404
__SC(32, clock_settime64, sys_clock_settime)
#define __NR_clock_adjtime64 405
__SC(32, clock_adjtime64, sys_clock_adjtime)
#define __NR_clock_getres_time64 406
__SC(32, clock_getres_time64, sys_clock_getres)
#define __NR_clock_nanosleep_time64 407
__SC(32, clock_nanosleep_time64, sys_clock_nanosleep)
#define __NR_timer_gettime64 408
__SC(32, timer_gettime64, sys_timer_gettime)
#define __NR_timer_settime64 409
__SC(32, timer_settime64, sys_timer_settime)
#define __NR_timerfd_gettime64 410
__SC(32, timerfd_gettime64, sys_timerfd_gettime)
#define __NR_timerfd_settime64 411
__SC(32, timerfd_settime64, sys_timerfd_settime)
#define __NR_utimensat_time64 412
__SC(32, utimensat_time64, sys_utimensat)
#define __NR_pselect6_time64 413
__SCC(32, pselect6_time64, sys_pselect6, compat_sys_pselect6_time64)
#define __NR_ppoll_time64 414
__SCC(32, ppoll_time64, sys_ppoll, compat_sys_ppoll_time64)
#define __NR_io_pgetevents_time64 416
__SCC(32, io_pgetevents_time64, sys_io_pgetevents, compat_sys_io_pgetevents_time64)
#define __NR_recvmmsg_time64 417
__SCC(32, recvmmsg_time64, sys_recvmmsg, compat_sys_recvmmsg_time64)
#define __NR_mq_timedsend_time64 418
__SC(32, mq_timedsend_time64, sys_mq_timedsend)
#define __NR_mq_timedreceive_time64 419
__SC(32, mq_timedreceive_time64, sys_mq_timedreceive)
#define __NR_semtimedop_time64 420
__SC(32, semtimedop_time64, sys_semtimedop)
#define __NR_rt_sigtimedwait_time64 421
__SCC(32, rt_sigtimedwait_time64, sys_rt_sigtimedwait, compat_sys_rt_sigtimedwait_time64)
#define __NR_futex_time64 422
__SC(32, futex_time64, sys_futex)
#define __NR_sched_rr_get_interval_time64 423
__SC(32, sched_rr_get_interval_time64, sys_sched_rr_get_interval)
#endif

#define __NR_pidfd_send_signal 424
__SC(common, pidfd_send_signal, sys_pidfd_send_signal)
#define __NR_io_uring_setup 425
__SC(common, io_uring_setup, sys_io_uring_setup)
#define __NR_io_uring_enter 426
__SC(common, io_uring_enter, sys_io_uring_enter)
#define __NR_io_uring_register 427
__SC(common, io_uring_register, sys_io_uring_register)
#define __NR_open_tree 428
__SC(common, open_tree, sys_open_tree)
#define __NR_move_mount 429
__SC(common, move_mount, sys_move_mount)
#define __NR_fsopen 430
__SC(common, fsopen, sys_fsopen)
#define __NR_fsconfig 431
__SC(common, fsconfig, sys_fsconfig)
#define __NR_fsmount 432
__SC(common, fsmount, sys_fsmount)
#define __NR_fspick 433
__SC(common, fspick, sys_fspick)
#define __NR_pidfd_open 434
__SC(common, pidfd_open, sys_pidfd_open)
#define __NR_clone3 435
__SC(common, clone3, sys_clone3)
#define __NR_close_range 436
__SC(common, close_range, sys_close_range)
#define __NR_openat2 437
__SC(common, openat2, sys_openat2)
#define __NR_pidfd_getfd 438
__SC(common, pidfd_getfd, sys_pidfd_getfd)
#define __NR_faccessat2 439
__SC(common, faccessat2, sys_faccessat2)
#define __NR_process_madvise 440
__SC(common, process_madvise, sys_process_madvise)
#define __NR_epoll_pwait2 441
__SCC(common, epoll_pwait2, sys_epoll_pwait2, compat_sys_epoll_pwait2)
#define __NR_mount_setattr 442
__SC(common, mount_setattr, sys_mount_setattr)
#define __NR_quotactl_fd 443
__SC(common, quotactl_fd, sys_quotactl_fd)
#define __NR_landlock_create_ruleset 444
__SC(common, landlock_create_ruleset, sys_landlock_create_ruleset)
#define __NR_landlock_add_rule 445
__SC(common, landlock_add_rule, sys_landlock_add_rule)
#define __NR_landlock_restrict_self 446
__SC(common, landlock_restrict_self, sys_landlock_restrict_self)

#ifdef __ARCH_WANT_MEMFD_SECRET
#define __NR_memfd_secret 447
__SC(memfd_secret, memfd_secret, sys_memfd_secret)
#endif

#define __NR_process_mrelease 448
__SC(common, process_mrelease, sys_process_mrelease)
#define __NR_futex_waitv 449
__SC(common, futex_waitv, sys_futex_waitv)
#define __NR_set_mempolicy_home_node 450
__SC(common, set_mempolicy_home_node, sys_set_mempolicy_home_node)
#define __NR_cachestat 451
__SC(common, cachestat, sys_cachestat)
#define __NR_fchmodat2 452
__SC(common, fchmodat2, sys_fchmodat2)
#define __NR_map_shadow_stack 453
__SC(common, map_shadow_stack, sys_map_shadow_stack)
#define __NR_futex_wake 454
__SC(common, futex_wake, sys_futex_wake)
#define __NR_futex_wait 455
__SC(common, futex_wait, sys_futex_wait)
#define __NR_futex_requeue 456
__SC(common, futex_requeue, sys_futex_requeue)

#define __NR_statmount   457
__SC(common, statmount, sys_statmount)

#define __NR_listmount   458
__SC(common, listmount, sys_listmount)

#define __NR_lsm_get_self_attr 459
__SC(common, lsm_get_self_attr, sys_lsm_get_self_attr)
#define __NR_lsm_set_self_attr 460
__SC(common, lsm_set_self_attr, sys_lsm_set_self_attr)
#define __NR_lsm_list_modules 461
__SC(common, lsm_list_modules, sys_lsm_list_modules)

#define __NR_mseal 462
__SYSCALL(__NR_mseal, sys_mseal)

#define __NR_setxattrat 463
__SYSCALL(__NR_setxattrat, sys_setxattrat)
#define __NR_getxattrat 464
__SYSCALL(__NR_getxattrat, sys_getxattrat)
#define __NR_listxattrat 465
__SYSCALL(__NR_listxattrat, sys_listxattrat)
#define __NR_removexattrat 466
__SYSCALL(__NR_removexattrat, sys_removexattrat)

#define __NR_uretprobe 467
__SYSCALL(__NR_uretprobe, sys_uretprobe)

#undef __NR_syscalls
#define __NR_syscalls 468
