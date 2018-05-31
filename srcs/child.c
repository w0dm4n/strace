/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:59:34 by frmarinh          #+#    #+#             */
/*   Updated: 2018/05/26 15:59:36 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void		liberate_poor_child(t_child *child)
{
	if (child) {
		if (child->executable_path) {
			free(child->executable_path);
		}
		if (child->args) {
			for (int i = 0; child->args[i] != NULL; i++) {
				free(child->args[i]);
			}
			free(child->args);
		}
		free(child);
	}
}

int get_executable_from_args(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] != FLAG_DELIMITER) {
			return i;
		}
	}
	return -1;
}

t_child		*build_child(int argc, char **argv)
{
	t_child	*child		= NULL;
	int		process_pos	= 0;
	int		index_args	= 1;

	if (!(child = (t_child*)malloc(sizeof(struct s_child)))) {
		return (NULL);
	}
	child->logs = NULL;
	child->pid = -1;
	if ((process_pos = get_executable_from_args(argc, argv)) == -1)
		return (NULL);
	child->executable_path = strdup(argv[process_pos++]);
	if (!(child->args = (char**)malloc(sizeof(char*) * (argc)))) {
		return (NULL);
	}

	child->args[0] = strdup(child->executable_path);
	while (process_pos < argc) {
		child->args[index_args++] = strdup(argv[process_pos++]);
	}
	child->args[index_args] = NULL;
	return (child);
}

void		do_child(t_child *child)
{
	execvp(child->executable_path, child->args);
}
