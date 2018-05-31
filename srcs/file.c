/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 18:21:21 by frmarinh          #+#    #+#             */
/*   Updated: 2018/05/26 18:21:27 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static bool	check_env_path(t_child *child)
{
	char *env_paths = getenv("PATH");
	char *path = NULL;
	char executable[BUFFER_SIZE];
	bool result = false;

	if (strlen(child->executable_path) > (BUFFER_SIZE - 1)) {
		printf("Please..\n");
		exit(0);
	}
	memset(executable, 0, (BUFFER_SIZE - 1));
	if (env_paths != NULL && (path = strdup(env_paths)) != NULL) {
		char **paths = str_split(path, ':');

		for (int i = 0; paths[i] != NULL; i++) {
			snprintf(executable, sizeof(executable), "%s/%s", paths[i], child->executable_path);
			if (access(executable, F_OK) != -1) {
				strdel(&child->executable_path);
				child->executable_path = strdup(executable);
				result = true;
				break;
			}
		}
		strdel(&path);
		free_array(paths);
	}
	return result;
}


void		check_correct_path(t_child *child)
{
	char current_path[BUFFER_SIZE];
	char new_executable[BUFFER_SIZE];

	memset((char*)&current_path, 0, BUFFER_SIZE);
	memset((char*)&new_executable, 0, BUFFER_SIZE);
	if (child->executable_path[0] != '.' && child->executable_path[0] != '/')
	{
		if (check_env_path(child)) {
			return ;
		}

		getcwd(current_path, sizeof(current_path));
		snprintf((char*)&new_executable, sizeof(new_executable), "%s/%s", current_path, child->executable_path);
		strdel(&child->executable_path);
		child->executable_path = strdup((char*)&new_executable);
	}
}

bool		check_child_path(t_child *child)
{
	int			fd = 0;
	struct stat	buf;

	if ((fd = open(child->executable_path, O_RDONLY)) < 0) {
		get_error(true);
	}
	if (fstat(fd, &buf) < 0) {
		get_error(true);
	}
	if (!S_ISREG(buf.st_mode)) {
		printf("ft_strace: This is not a regular file.. what do you want me to do with it ?\n");
	}
	close(fd);
	return true;
}
