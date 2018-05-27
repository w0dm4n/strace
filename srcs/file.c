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

bool		check_file(char *path)
{
	int			fd = 0;
	struct stat	buf;

	if ((fd = open(path, O_RDONLY)) < 0) {
		get_error(true);
	}
	if (fstat(fd, &buf) < 0) {
		get_error(true);
	}
	if (!S_ISREG(buf.st_mode)) {
		printf("ft_strace: This is not a regular file.. what do you want me to do with it ?\n");
	}
	return true;
}
