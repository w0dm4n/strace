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
# include <unistd.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/ptrace.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/reg.h>
# include <sys/user.h>
# include <stdarg.h>
# include <assert.h>

#define SUCCESS_ERRNO_MSG "Success"

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
**	FILE
*/
bool			check_file(char *path);

/*
**	CHILD
*/
typedef struct	s_child
{
	pid_t		pid;
	char		*executable_path;
	char		**args;
	char		**env;
}				t_child;

t_child			*build_child(int argc, char **argv);
void			liberate_poor_child(t_child *child);
void			do_child(t_child *child);
void			check_correct_path(t_child *child);

/*
**	TRACER
*/
void			do_trace(t_child *child);
char			*read_string(pid_t pid, long registery_address);
long			reg_from_position(struct user_regs_struct *regs, int arg);

/*
**	UTILS
*/
void			get_error(bool exit_program);
char			*str_replace(char *orig, char *rep, char *with);
void			strdel(char **ptr);
char			*strschr(char *orig, char *rep);
char			**str_split(char* a_str, const char a_delim);
int				array_len(char **array);
void			free_array(char **array);

/*
**	SYSCALLS
*/
char			*get_syscall_name(int syscall_index);
char			*print_syscall_args(int syscall_n, struct user_regs_struct *regs, t_child *child);

#endif
