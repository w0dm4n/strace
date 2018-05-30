/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 21:09:05 by frmarinh          #+#    #+#             */
/*   Updated: 2018/05/29 21:09:11 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*get_syscall_args_type(int syscall_index)
{
	const char *SYSCALL_ARGS[] = {
		"%d, %s, %ld",
		"%d, %s, %ld",
		"%s, %d",
		"%d",
		"%s, %p",
		"%d, %p",
		"%s, %p",
		"%p, %d, %d",
		"%d, %lld, %d",
		"%p, %ld, %d, %d, %d, %ld",
		"%p, %ld, %ld",
		"%p, %ld",
		"%ld",
		"%p, %p, %p, %ld",
		"%d, %p, %p, %ld",
		"%ld",
		"%d, %d, %ld",
		"%d, %s, %ld, %lld",
		"%d, %s, %ld, %lld",
		"%ld, %p, %ld",
		"%ld, %p, %ld",
		"%s, %d",
		"%d",
		"%d, %p, %p, %p, %p",
		"",
		"%ld, %ld, %ld, %ld, %ld",
		"%ld, %ld, %d",
		"%ld, %ld, %s",
		"%ld, %ld, %d",
		"%p, %ld, %d",
		"%d, %s, %d",
		"%d, %d, %p",
		"%d",
		"%d, %d",
		"",
		"%p, %p",
		"%d, %p",
		"%d",
		"%d, %p, %p",
		"",
		"%d, %d, %lld, %ld",
		"%d, %d, %d",
		"%d, %p, %d",
		"%d, %p, %d",
		"%d, %p, %ld, %p, %p, %d",
		"%d, %p, %ld, %p, %p, %d",
		"%d, %p, %p",
		"%d, %p, %p",
		"%d, %d",
		"%d, %p, %d",
		"%d, %d",
		"%d, %p, %d",
		"%d, %p, %d",
		"%d, %d, %d, %d",
		"%d, %d, %d, %s, %d",
		"%d, %d, %d, %s, %d",
		"%ld, %ld, %d, %d, %ld",
		"",
		"",
		"%s, %p, %p",
		"%d",
		"%ld, %d, %d, %p",
		"%d, %d",
		"%p",
		"%p, %d, %d",
		"%d, %p, %p",
		"%d, %d, %d, %ld",
		"%s",
		"%p, %d",
		"%d, %p, %ld, %d",
		"%d, %p, %ld, %ld, %d",
		"%d, %d, %p",
		"%d, %d, %ld",
		"%d, %d",
		"%d",
		"%d",
		"%s, %ld",
		"%d, %ld",
		"%d, %p, %d",
		"%s, %ld",
		"%s",
		"%d",
		"%s, %s",
		"%s, %d",
		"%s",
		"%s, %d",
		"%s, %s",
		"%s",
		"%s, %s",
		"%s, %s, %d",
		"%s, %d",
		"%d, %d",
		"%s, %ld, %ld",
		"%d, %ld, %ld",
		"%s, %ld, %ld",
		"%d",
		"%p, %p",
		"%d, %p",
		"%d, %p",
		"%p",
		"%p",
		"%ld, %ld, %ld, %ld",
		"",
		"%d, %s, %d",
		"",
		"%ld",
		"%ld",
		"",
		"",
		"%ld, %ld",
		"",
		"",
		"",
		"%ld, %ld",
		"%ld, %ld",
		"%d, %ld",
		"%d, %ld",
		"%ld, %ld, %ld",
		"%ld, %ld, %ld",
		"%ld, %ld, %ld",
		"%ld, %ld, %ld",
		"%ld",
		"%ld",
		"%ld",
		"%ld",
		"%p, %p",
		"%p, %p",
		"%p, %ld",
		"%p, %p, %p, %ld",
		"%d, %d, %p",
		"%p, %ld",
		"%p, %p",
		"%s, %p",
		"%s, %d, %p",
		"%s",
		"%d",
		"%p, %p",
		"%s, %p",
		"%d, %p",
		"%d, %ld, %ld",
		"%d, %d",
		"%d, %d, %d",
		"%ld, %p",
		"%ld, %p",
		"%ld, %d, %p",
		"%ld",
		"%d",
		"%d",
		"%ld, %p",
		"%ld, %ld",
		"%ld, %ld",
		"%d",
		"",
		"",
		"%d, %p, %ld",
		"%s, %s",
		"%p",
		"%d, %ld, %ld, %ld, %ld",
		"%d, %ld",
		"%p",
		"%d, %p",
		"%s",
		"",
		"%s",
		"%p, %p",
		"%s, %s, %s, %ld, %p",
		"%p, %d",
		"%s, %d",
		"%s",
		"%d, %d, %d, %p",
		"%s, %d",
		"%s, %d",
		"%d",
		"%ld, %ld, %d",
		"%p, %ld",
		"%p, %ld, %s",
		"%s, %d",
		"%p",
		"%p, %d, %p, %ld, %ld",
		"%d, %s, %ld, %p",
		"%d, %p, %p",
		"%p",
		"%p",
		"%p",
		"%p",
		"%p",
		"",
		"%d, %lld, %ld",
		"%s, %s, %p, %ld, %d",
		"%s, %s, %p, %ld, %d",
		"%d, %s, %p, %ld, %d",
		"%s, %s, %p, %ld",
		"%s, %s, %p, %ld",
		"%d, %s, %p, %ld",
		"%s, %s, %ld",
		"%s, %s, %ld",
		"%d, %s, %ld",
		"%s, %s",
		"%s, %s",
		"%d, %s",
		"%d, %d",
		"%p",
		"%p, %d, %p, %p, %p, %p",
		"%ld, %d, %ld",
		"%ld, %d, %ld",
		"%p",
		"%p, %p",
		"%p",
		"%p, %ld, %ld, %p, %p",
		"%p, %ld, %p",
		"%p, %p, %p",
		"%p",
		"%p, %s, %ld",
		"%d",
		"%p",
		"%p",
		"%ld, %ld, %ld, %ld, %ld",
		"%d, %p, %d",
		"%d",
		"",
		"%d, %p, %p, %p",
		"%d, %lld, %ld, %d",
		"%ld, %p, %p",
		"%p, %d, %p, %p",
		"%p, %p",
		"%p",
		"%p",
		"%ld, %p",
		"%ld, %p",
		"%ld, %p",
		"%ld, %d, %p, %p",
		"%d",
		"%d, %p, %d, %d",
		"%d, %d, %d, %p",
		"%d, %d, %d",
		"%s, %p",
		"%p",
		"%ld, %ld, %ld, %ld, %ld, %p",
		"%d, %ld, %ld",
		"%d, %ld, %ld, %ld, %ld",
		"%s, %d, %d, %p",
		"%s",
		"%p, %s, %ld, %d, %p",
		"%p, %s, %ld, %d, %p",
		"%p, %p",
		"%p, %p, %p",
		"%ld, %ld, %p, %ld",
		"%d, %ld, %p, %d, %p",
		"%s, %s, %p, %ld, %p",
		"%s, %s, %s, %p",
		"%d, %ld, %ld, %ld, %ld",
		"%d, %d, %d",
		"%d, %d",
		"",
		"%d, %s, %p",
		"%d, %p",
		"%ld, %ld, %ld, %ld",
		"%d, %s, %d, %d",
		"%d, %s, %d",
		"%d, %s, %d, %p",
		"%d, %s, %ld, %ld, %d",
		"%d, %s, %p",
		"%d, %s, %p, %d",
		"%d, %s, %d",
		"%d, %s, %d, %s",
		"%d, %s, %d, %s, %d",
		"%s, %d, %s",
		"%d, %s, %s, %d",
		"%d, %s, %d",
		"%d, %s, %d",
		"%d, %p, %p, %p, %p, %p",
		"%p, %d, %p, %p, %ld",
		"%ld",
		"%p, %ld",
		"%d, %p, %ld",
		"%d, %lld, %d, %lld, %ld, %d",
		"%d, %d, %ld, %d",
		"%d, %lld, %lld, %d",
		"%d, %p, %ld, %d",
		"%ld, %ld, %p, %d, %d, %d",
		"%d, %s, %p, %d",
		"%d, %p, %d, %d, %p, %ld",
		"%d, %p, %ld",
		"%p",
		"%d",
		"%d, %d, %lld, %lld",
		 NULL
	};
	if (syscall_index >= 0 && syscall_index < array_len((char**)&SYSCALL_ARGS[0])) {
		return strdup(SYSCALL_ARGS[syscall_index]);
	}
	return NULL;
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

char		*get_syscall_return_type(int syscall_index)
{
	char* SYSCALL_RETS[] = {
		"%ld",
		"",
		"%d",
		"%d",
		"",
		"%d",
		"%d",
		"",
		"%lld",
		"%p",
		"%d",
		"%d",
		"%p",
		"",
		"%d",
		"",
		"",
		"",
		"",
		"%ld",
		"%ld",
		"%d",
		"%d",
		"",
		"%d",
		"%p",
		"%d",
		"%d",
		"%d",
		"%d",
		"%p",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%ld",
		"",
		"",
		"%d",
		"%d",
		"%ld",
		"%ld",
		"%ld",
		"%ld",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%ld",
		"%ld",
		"%d",
		"%p",
		"%ld",
		"",
		"",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%ld",
		"%d",
		"",
		"",
		"%d",
		"%d",
		"",
		"%d",
		"%d",
		"%s",
		"%d",
		"%d",
		"",
		"",
		"",
		"%d",
		"",
		"",
		"%d",
		"",
		"",
		"%d",
		"",
		"%d",
		"%d",
		"%p",
		"%d",
		"%d",
		"%d",
		"",
		"",
		"",
		"%ld",
		"",
		"%ld",
		"%d",
		"%d",
		"%ld",
		"%ld",
		"%d",
		"%ld",
		"%ld",
		"",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%ld",
		"%d",
		"%d",
		"%ld",
		"%d",
		"%d",
		"",
		"",
		"%d",
		"",
		"%d",
		"",
		"",
		"%d",
		"",
		"",
		"",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"",
		"%d",
		"",
		"%d",
		"%d",
		"%d",
		"",
		"",
		"%d",
		"%d",
		"",
		"%d",
		"",
		"",
		"",
		"%d",
		"%d",
		"%d",
		"%d",
		"%p",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%ld",
		"",
		"",
		"",
		"",
		"",
		"%ld",
		"%ld",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"%d",
		"",
		"",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"",
		"",
		"%d",
		"%d",
		"%ld",
		"%d",
		"%d",
		"",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%p",
		"%d",
		"%d",
		"%d",
		"%d",
		"",
		"%ld",
		"%ld",
		"%d",
		"%p",
		"%d",
		"%d",
		"%ld",
		"%d",
		"%d",
		"%ld",
		"%d",
		"%p",
		"%p",
		"%ld",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"%ld",
		"%d",
		"%d",
		"%d",
		"%d",
		"%d",
		"",
		"%d",
		"%d",
		"%d",
		"%d",
		"%ld",
		"%d",
		"%d",
		"",
		"%d",
		"",
		"%ld",
		"%ld",
		"%ld",
		"",
		"%d",
		"%ld",
		"%ld",
		"%d",
		"%d",
		"",
		"",
		"",
		"",
		NULL
	};
	if (syscall_index >= 0 && syscall_index < array_len((char**)&SYSCALL_RETS[0])) {
		return (SYSCALL_RETS[syscall_index]);
	}
	return "%p";
}
