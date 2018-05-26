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
	child->executable_path = strdup(argv[1]);
	if (!(child->args = (char**)malloc(sizeof(char*) * (argc-1)))) {
		return (NULL);
	}
	for (int i = 2; i < argc; i++) {
		child->args[(i-2)] = strdup(argv[i]);
	}
	child->args[argc-2] = NULL;
	return (child);
}
