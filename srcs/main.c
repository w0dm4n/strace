#include "all.h"

static void	print_help()
{
	printf("usage: ft_strace [-cCh] PROG [ARGS]\n");
	exit(0);
}

int			main(int argc, char **argv)
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

		for (int i = 0; child->args[i] != NULL; i++) {
			printf("%s\n", child->args[i]);
		}
		liberate_poor_child(child);
	} else {
		printf("ft_strace: must have PROG [ARGS] or -p PID\n" \
			"Try 'ft_strace -h' for more information.\n");
	}
	return (0);
}
