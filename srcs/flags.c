/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 16:12:49 by frmarinh          #+#    #+#             */
/*   Updated: 2018/05/26 16:13:02 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void				add_flag(char *str)
{
	t_flags *flags = NULL;

	if ((flags = get_flags()) == NULL)
		return ;
	if (strlen(str) == 2) {
		for (int i = 0; i < MAX_FLAGS; i++) {
			if (flags->enabled[i] == UNACTIVE_FLAG) {
				flags->enabled[i] = str[1];
			}
		}
	}
}

t_flags				*get_flags()
{
	static t_flags *flags = NULL;

	if (flags != NULL) {
		return flags;
	} else {
		if (!(flags = (t_flags*)malloc(sizeof(struct s_flags)))) {
			return NULL;
		}
		for (int i = 0; i < MAX_FLAGS; i++) {
			flags->enabled[i] = 0;
		}
		return flags;
	}
}

bool				flag_active(FLAG f)
{
	t_flags *flags = NULL;

	if ((flags = get_flags()) == NULL)
		return false;
	for (int i = 0; i < MAX_FLAGS; i++) {
		if (flags->enabled[i] == f) {
			return true;
		}
	}
	return false;
}
