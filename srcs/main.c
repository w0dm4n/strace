#include "all.h"

static void	print_help()
{
	printf("usage: ft_strace [-cCh] PROG [ARGS]\n");
	exit(0);
}

static void signalHandler(int signo)
{
	if (g_child != NULL && g_child->pid != 0) {
		ptrace(PTRACE_DETACH, g_child->pid, 0);
		kill(g_child->pid, SIGKILL);
		printf("ft_strace: Process %d detached\n", g_child->pid);
	}
}

static void signals()
{
	static sigset_t empty_set, blocked_set;
	struct sigaction sa;

	sa.sa_handler = SIG_IGN; /* Ignore signal flag */
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigaction(SIGTTOU, &sa, NULL); // Terminal access out
	sigaction(SIGTTIN, &sa, NULL); // Terminal access in
	sigaction(SIGHUP, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGPIPE, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGBUS, &sa, NULL);
	sigemptyset(&empty_set);
	sigemptyset(&blocked_set);

	sigprocmask(SIG_SETMASK, &empty_set, NULL);
	sigprocmask(SIG_BLOCK, &blocked_set, NULL);

	sigaddset(&blocked_set, SIGHUP);
	sigaddset(&blocked_set, SIGQUIT);
	sigaddset(&blocked_set, SIGPIPE);
	sigaddset(&blocked_set, SIGTERM);

	signal(SIGCHLD, SIG_IGN);
	signal(SIGINT, signalHandler);
}

static void do_fork(t_child *child)
{
	check_correct_path(child);

	if (check_child_path(child)) {
		child->pid = fork();

		if (child->pid == 0) {
			do_child(child);
		} else {
			signals();
			do_trace(child);
		}
	}
}

int			main(int argc, char **argv, char **env)
{
 	if (argc >= 2) {
		g_child = NULL;
		t_child	*child = NULL;

		if (!(child = build_child(argc, argv))) {
			print_help();
		}
		for (int i = 1; i < argc; i++) {
			if (argv[i][0] == FLAG_DELIMITER) {
				add_flag(argv[i]);
			}
		}
		if (flag_active(HELP_FLAG)) {
			print_help();
		}
		do_fork(child);
		liberate_poor_child(child);
	} else {
		printf("ft_strace: must have PROG [ARGS] or -p PID\n" \
			"Try 'ft_strace -h' for more information.\n");
	}
	return (0);
}
