/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 20:48:07 by frmarinh          #+#    #+#             */
/*   Updated: 2018/05/27 20:48:16 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

int		count_args(char *syscall_args)
{
	int args_count = 0;
	for (int i = 0; i < strlen(syscall_args); i++) {
		if (syscall_args[i] == '%')
			args_count++;
	}
	return args_count;
}

int		position_current_arg(char *pos, char *args)
{
	int arg_position = 0;
	for (int i = 0; i < strlen(args) && args != pos; i++)
	{
		if (args[i] == ',') {
			arg_position++;
		}
		*args++;
	}
	return arg_position;
}

void	append_result(int len, int pos, char *result, char *to_add, bool string)
{
	int result_len = strlen(result);
	if (!string) {
		if (pos != len-1) {
			snprintf(result + strlen(result), (BUFFER_SIZE - 1) - result_len, "%s, ", to_add);
		} else {
			snprintf(result + strlen(result), (BUFFER_SIZE - 1) - result_len, "%s", to_add);
		}
	} else {
		if (pos != len-1) {
			snprintf(result + strlen(result), (BUFFER_SIZE - 1) - result_len, "\"%s\", ", to_add);
		} else {
			snprintf(result + strlen(result), (BUFFER_SIZE - 1) - result_len, "\"%s\"", to_add);
		}
	}
}

char	*parse_datas(char *raw_args, struct user_regs_struct *regs, t_child *child)
{
	char *result = NULL;
	char *content = NULL;
	char *save_ptr = NULL;

	if (!(result = (char*)malloc(sizeof(char) * BUFFER_SIZE))
		|| !(content = (char*)malloc(sizeof(char) * BUFFER_SIZE)))
		return (NULL);
	memset(result, 0, (BUFFER_SIZE - 1));
	char **args = str_split(raw_args, ',');
	if (args == NULL) {
		strdel(&content);
		return result;
	}
	int len = array_len(args);
	for (int i = 0; args[i] != NULL; i++) {
		save_ptr = args[i];
		args[i] = str_replace(args[i], " ", "");

		strdel(&save_ptr);
		memset(content, 0, (BUFFER_SIZE - 1));
		long registery_address = reg_from_position(regs, i);
		if (registery_address != -1) {
			if (strschr(args[i], "%s") == NULL) {
				snprintf(content, (BUFFER_SIZE - 1), args[i], registery_address);
				append_result(len, i, result, content, false);
			} else {

				char *arg_content = read_string(child->pid, registery_address);
				save_ptr = arg_content;
				arg_content = str_replace(arg_content, "\n", "\\n");

				append_result(len, i, result, arg_content, true);
				strdel(&save_ptr);
				strdel(&arg_content);
			}
		}
	}

	free_array(args);
	strdel(&content);
	return result;
}

char	*get_syscall_args(int syscall_n, struct user_regs_struct *regs, t_child *child)
{
	char *args = get_syscall_args_type(syscall_n);
	char *datas = NULL;
	if (!args) {
		return NULL;
	}
	datas = parse_datas(args, regs, child);
	strdel(&args);
	return datas;
}

char	*get_syscall_return(int syscall_n, struct user_regs_struct *regs)
{
	char *result = NULL;

	if (!(result = (char*)malloc(sizeof(char) * BUFFER_SIZE)))
		return NULL;
	memset(result, 0, (BUFFER_SIZE - 1));
	char *type = get_syscall_return_type(syscall_n);
	if (strlen(type) > 0) {
		if ((void*)regs->rax != NULL)  { 
			snprintf(result, (BUFFER_SIZE - 1), type, regs->rax);

		} else {
			snprintf(result, (BUFFER_SIZE - 1), "0");
		}
	}
	return result;
}
