/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:58:16 by frmarinh          #+#    #+#             */
/*   Updated: 2018/05/26 15:58:18 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/ptrace.h>
# include <string.h>
# include <stdlib.h>

# define FLAG_DELIMITER '-'
# define bool			int
# define false			0
# define true			1

/*
**	FLAGS
*/
# define FLAG			char
# define MAX_FLAGS		16
# define HELP_FLAG		'h'
# define INFOS_FLAG		'c'
# define UNACTIVE_FLAG	0

typedef struct	s_flags
{
	FLAG		enabled[MAX_FLAGS];
}				t_flags;

void			add_flag(char *str);
t_flags			*get_flags();
bool			flag_active(FLAG f);

/*
**	CHILD
*/
typedef struct	s_child
{
	char		*executable_path;
	char		**args;
}				t_child;

t_child			*build_child(int argc, char **argv);
void			liberate_poor_child(t_child *child);
#endif
