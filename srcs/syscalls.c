/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 20:48:07 by frmarinh          #+#    #+#             */
/*   Updated: 2018/05/27 20:48:16 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		count_args(char *syscall_args)
{
	int args_count = 0;
	for (int i = 0; i < strlen(syscall_args); i++) {
		if (syscall_args[i] == '%')
			args_count++;
	}
	return args_count;
}

char	*get_syscall_args(int syscall_index)
{
	char *SYSCALL_ARGS[] = {
		"%d, %s, %lu",
		"%d, %s, %lu",
		"%s, %d",
		"%d",
		"%p, %p",
		"%d, %p",
		NULL
	};
	if (syscall_index >= 0 && syscall_index < array_len((char**)&SYSCALL_ARGS[0])) {
		return strdup(SYSCALL_ARGS[syscall_index]);
	}
	return NULL;
}

int		position_current_arg(char *pos, char *args)
{
	int arg_position = 0;
	for (int i = 0; i < strlen(args) && args != pos; i++)
	{
		if (args[i] == ',') {
			arg_position++;
		}
		*args++;
	}
	return arg_position;
}

void	append_result(int len, int pos, char *result, char *to_add, bool string)
{
	if (!string) {
		if (pos != len-1) {
			snprintf(result + strlen(result), 1023, "%s, ", to_add);
		} else {
			snprintf(result + strlen(result), 1023, "%s", to_add);
		}
	} else {
		if (pos != len-1) {
			snprintf(result + strlen(result), 1023, "\"%s\", ", to_add);
		} else {
			snprintf(result + strlen(result), 1023, "\"%s\"", to_add);
		}
	}
}

char	*parse_datas(char *raw_args, struct user_regs_struct *regs, t_child *child)
{
	char *result = NULL;
	char *content = NULL;
	char *save_ptr = NULL;

	if (!(result = (char*)malloc(sizeof(char) * 1024))
		|| !(content = (char*)malloc(sizeof(char) * 1024)))
		return (NULL);
	memset(result, 0, 1023);
	char **args = str_split(raw_args, ',');
	int len = array_len(args);
	for (int i = 0; args[i] != NULL; i++) {
		save_ptr = args[i];
		args[i] = str_replace(args[i], " ", "");

		strdel(&save_ptr);
		memset(content, 0, 1023);
		long registery_address = reg_from_position(regs, i);
		if (registery_address != -1) {
			if (strschr(args[i], "%s") == NULL) {
				snprintf(content, 1023, args[i], registery_address);
				append_result(len, i, result, content, false);
			} else {

				char *arg_content = read_string(child->pid, registery_address);
				save_ptr = arg_content;
				arg_content = str_replace(arg_content, "\n", "\\n");

				append_result(len, i, result, arg_content, true);
				strdel(&save_ptr);
				strdel(&arg_content);
			}
		}
	}

	free_array(args);
	strdel(&content);
	strdel(&raw_args);
	return result;
}

char	*print_syscall_args(int syscall_n, struct user_regs_struct *regs, t_child *child)
{
	char *args = get_syscall_args(syscall_n);
	if (!args) {
		return NULL;
	}
	return parse_datas(args, regs, child);
}

char	*get_syscall_name(int syscall_index)
{
	char* SYSCALL_NAMES[] = {
	    "read",
	    "write",
	    "open",
	    "close",
	    "stat",
	    "fstat",
	    "lstat",
	    "poll",
	    "lseek",
	    "mmap",
	     "mprotect",
	     "munmap",
	     "brk",
	     "rt_sigaction",
	     "rt_sigprocmask",
	     "rt_sigreturn",
	     "ioctl",
	     "pread64",
	     "pwrite64",
	     "readv",
	     "writev",
	     "access",
	     "pipe",
	     "select",
	     "sched_yield",
	     "mremap",
	     "msync",
	     "mincore",
	     "madvise",
	     "shmget",
	     "shmat",
	     "shmctl",
	     "dup",
	     "dup2",
	     "pause",
	     "nanosleep",
	     "getitimer",
	     "alarm",
	     "setitimer",
	     "getpid",
	     "sendfile",
	     "socket",
	     "connect",
	     "accept",
	     "sendto",
	     "recvfrom",
	     "sendmsg",
	     "recvmsg",
	     "shutdown",
	     "bind",
	     "listen",
	     "getsockname",
	    "getpeername",
	    "socketpair",
	    "setsockopt",
	    "getsockopt",
	    "clone",
	    "fork",
	    "vfork",
	    "execve",
	    "exit",
	    "wait4",
	    "kill",
	    "uname",
	    "semget",
	    "semop",
	    "semctl",
	    "shmdt",
	    "msgget",
	    "msgsnd",
	    "msgrcv",
	    "msgctl",
	    "fcntl",
	    "flock",
	    "fsync",
	    "fdatasync",
	    "truncate",
	    "ftruncate",
	    "getdents",
	    "getcwd",
	    "chdir",
	    "fchdir",
	    "rename",
	    "mkdir",
	    "rmdir",
	    "creat",
	    "link",
	    "unlink",
	    "symlink",
	    "readlink",
	    "chmod",
	    "fchmod",
	    "chown",
	    "fchown",
	    "lchown",
	    "umask",
	    "gettimeofday",
	    "getrlimit",
	    "getrusage",
	    "sysinfo",
	    "times",
	    "ptrace",
	    "getuid",
	    "syslog",
	    "getgid",
	    "setuid",
	    "setgid",
	    "geteuid",
	    "getegid",
	    "setpgid",
	    "getppid",
	    "getpgrp",
	    "setsid",
	    "setreuid",
	    "setregid",
	    "getgroups",
	    "setgroups",
	    "setresuid",
	    "getresuid",
	    "setresgid",
	    "getresgid",
	    "getpgid",
	    "setfsuid",
	    "setfsgid",
	    "getsid",
	    "capget",
	    "capset",
	    "rt_sigpending",
	    "rt_sigtimedwait",
	    "rt_sigqueueinfo",
	    "rt_sigsuspend",
	    "sigaltstack",
	    "utime",
	    "mknod",
	    "uselib",
	    "personality",
	    "ustat",
	    "statfs",
	    "fstatfs",
	    "sysfs",
	    "getpriority",
	   "setpriority",
	   "sched_setparam",
	   "sched_getparam",
	   "sched_setscheduler",
	   "sched_getscheduler",
	   "sched_get_priority_max",
	   "sched_get_priority_min",
	   "sched_rr_get_interval",
	   "mlock",
	   "munlock",
	   "mlockall",
	    "munlockall",
	    "vhangup",
	    "modify_ldt",
	    "pivot_root",
	    "_sysctl",
	    "prctl",
	    "arch_prctl",
	    "adjtimex",
	    "setrlimit",
	    "chroot",
	    "sync",
	    "acct",
	    "settimeofday",
	    "mount",
	    "umount2",
	    "swapon",
	    "swapoff",
	    "reboot",
	    "sethostname",
	    "setdomainname",
	    "iopl",
	    "ioperm",
	    "create_module",
	    "init_module",
	    "delete_module",
	    "get_kernel_syms",
	    "query_module",
	    "quotactl",
	    "nfsservctl",
	    "getpmsg",
	    "putpmsg",
	    "afs_syscall",
	    "tuxcall",
	    "security",
	    "gettid",
	    "readahead",
	    "setxattr",
	    "lsetxattr",
	    "fsetxattr",
	    "getxattr",
	    "lgetxattr",
	    "fgetxattr",
	    "listxattr",
	    "llistxattr",
	    "flistxattr",
	    "removexattr",
	    "lremovexattr",
	    "fremovexattr",
	    "tkill",
	    "time",
	    "futex",
	    "sched_setaffinity",
	    "sched_getaffinity",
	    "set_thread_area",
	    "io_setup",
	    "io_destroy",
	    "io_getevents",
	    "io_submit",
	    "io_cancel",
	    "get_thread_area",
	    "lookup_dcookie",
	    "epoll_create",
	    "epoll_ctl_old",
	    "epoll_wait_old",
	    "remap_file_pages",
	    "getdents64",
	    "set_tid_address",
	    "restart_syscall",
	    "semtimedop",
	    "fadvise64",
	    "timer_create",
	    "timer_settime",
	    "timer_gettime",
	    "timer_getoverrun",
	    "timer_delete",
	    "clock_settime",
	    "clock_gettime",
	    "clock_getres",
	    "clock_nanosleep",
	    "exit_group",
	    "epoll_wait",
	    "epoll_ctl",
	    "tgkill",
	    "utimes",
	    "vserver",
	    "mbind",
	    "set_mempolicy",
	    "get_mempolicy",
	    "mq_open",
	    "mq_unlink",
	    "mq_timedsend",
	    "mq_timedreceive",
	    "mq_notify",
	    "mq_getsetattr",
	    "kexec_load",
	    "waitid",
	    "add_key",
	    "request_key",
	    "keyctl",
	    "ioprio_set",
	    "ioprio_get",
	    "inotify_init",
	    "inotify_add_watch",
	    "inotify_rm_watch",
	    "migrate_pages",
	    "openat",
	    "mkdirat",
	    "mknodat",
	    "fchownat",
	    "futimesat",
	    "newfstatat",
	    "unlinkat",
	    "renameat",
	    "linkat",
	    "symlinkat",
	    "readlinkat",
	    "fchmodat",
	    "faccessat",
	    "pselect6",
	    "ppoll",
	    "unshare",
	    "set_robust_list",
	    "get_robust_list",
	    "splice",
	    "tee",
	    "sync_file_range",
	    "vmsplice",
	    "move_pages",
	    "utimensat",
	    "epoll_pwait",
	    "signalfd",
	    "timerfd",
	    "eventfd",
	    "fallocate",
		NULL
	};
	if (syscall_index >= 0 && syscall_index < array_len((char**)&SYSCALL_NAMES[0])) {
		return (SYSCALL_NAMES[syscall_index]);
	}
	return NULL;
}
