#include "all.h"

static void	print_help()
{
	printf("usage: ft_strace [-cCh] PROG [ARGS]\n");
	exit(0);
}

static void do_fork(t_child *child)
{
	check_correct_path(child);

	if (check_file(child->executable_path)) {
		child->pid = fork();

		if (child->pid == 0) {
			do_child(child);
		} else {
			do_trace(child);
		}
	}
}

int			main(int argc, char **argv, char **env)
{
 	if (argc >= 2) {
		t_child	*child = NULL;

		if (!(child = build_child(argc, argv))) {
			return (-1);
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
