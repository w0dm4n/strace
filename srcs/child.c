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

t_child		*build_child(int argc, char **argv)
{
	t_child	*child = NULL;

	if (!(child = (t_child*)malloc(sizeof(struct s_child)))) {
		return (NULL);
	}
	child->pid = -1;
	child->executable_path = strdup(argv[1]);
	if (!(child->args = (char**)malloc(sizeof(char*) * (argc)))) {
		return (NULL);
	}
	child->args[0] = strdup(child->executable_path);
	for (int i = 2; i < argc; i++) {
		child->args[(i-1)] = strdup(argv[i]);
	}
	child->args[argc-1] = NULL;
	return (child);
}

void		check_correct_path(t_child *child)
{
	char current_path[1024];
	char new_executable[1024];

	memset((char*)&current_path, 0, 1024);
	memset((char*)&new_executable, 0, 1024);
	if (child->executable_path[0] != '.' && child->executable_path[0] != '/')
	{
		getcwd(current_path, sizeof(current_path));
		snprintf((char*)&new_executable, sizeof(new_executable), "%s/%s", current_path, child->executable_path);
		free(child->executable_path);
		child->executable_path = strdup((char*)&new_executable);
	}
}

void		do_child(t_child *child)
{
	execvp(child->executable_path, child->args);
}
