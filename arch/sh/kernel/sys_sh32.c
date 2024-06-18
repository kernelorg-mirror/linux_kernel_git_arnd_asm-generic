// SPDX-License-Identifier: GPL-2.0
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/sched/task_stack.h>
#include <linux/mm.h>
#include <linux/smp.h>
#include <linux/sem.h>
#include <linux/msg.h>
#include <linux/shm.h>
#include <linux/stat.h>
#include <linux/syscalls.h>
#include <linux/mman.h>
#include <linux/file.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/ipc.h>
#include <asm/cacheflush.h>
#include <linux/uaccess.h>
#include <asm/unistd.h>
#include <asm/syscalls.h>

/*
 * sys_pipe() is the normal C calling standard for creating
 * a pipe. It's not the way Unix traditionally does this, though.
 */
asmlinkage int sys_sh_pipe(void)
{
	int fd[2];
	int error;

	error = do_pipe_flags(fd, 0);
	if (!error) {
		current_pt_regs()->regs[1] = fd[1];
		return fd[0];
	}
	return error;
}
