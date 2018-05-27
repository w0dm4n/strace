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

# define FLAG_DELIMITER '-'
# define bool			int
# define false			0
# define true			1

/*
**	REGISTERY DEFINE
*/
#define SNPRINTF(...) snprintf(result, 1023, args, __VA_ARGS__)
#define FUN(...) fn(void, (char *result, char *args, struct user_regs_struct *regs), { __VA_ARGS__; })
#define RDI regs->rdi
#define RSI regs->rsi
#define RDX regs->rdx
#define R10 regs->r10
#define R8 regs->r8
#define R9 regs->r9

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
void			getdata(pid_t child, long addr, char *str, int len);

/*
**	UTILS
*/
void			get_error(bool exit_program);

/*
**	SYSCALLS
*/
char			*get_syscall_name(int syscall_index);
char			*print_syscall_args(int syscall_n, struct user_regs_struct *regs);

#endif
