/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 02:00:07 by frmarinh          #+#    #+#             */
/*   Updated: 2018/05/31 02:00:08 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_syscall	*new_log(int id, char *syscall, bool error, float cpu_time)
{
	t_syscall *new = NULL;

	if (!(new = (t_syscall*)malloc(sizeof(struct s_syscall))))
		return NULL;
	new->id = id;
	new->name = strdup(syscall);
	new->errors = (error) ? 1 : 0;
	new->calls = (!error) ? 1 : 0;
	new->cpu_time = cpu_time;
	new->next = NULL;
	return new;
}

t_syscall	*get_log(t_child *child, int id)
{
	for (t_syscall *logs = child->logs; logs != NULL; logs = logs->next) {
		if (logs->id == id) {
			return logs;
		}
	}
	return (NULL);
}

void		append_logs(t_child *child, t_syscall *new_log)
{
	if (new_log) {
		t_syscall *logs = child->logs;
		while (logs->next)
			logs = logs->next;
		logs->next = new_log;
	}
}

void		update_log(t_syscall *log_sys, bool error, float cpu_time)
{
	if (error) {
		log_sys->errors += 1;
	} else {
		log_sys->calls += 1;
	}
	log_sys->cpu_time += cpu_time;
}

void		add_log(t_child *child, int id, char *syscall, bool error, float cpu_time)
{
	t_syscall *new = NULL;
	t_syscall *existing_log = get_log(child, id);

	if (child->logs) {
		if (existing_log) {
			update_log(existing_log, error, cpu_time);
		} else {
			append_logs(child, new_log(id, syscall, error, cpu_time));
		}
	} else {
		child->logs = new_log(id, syscall, error, cpu_time);
	}
}

void		free_logs(t_child *child)
{
	t_syscall *logs = child->logs;
	t_syscall *next = NULL;

	while (logs)
	{
		next = logs->next;
		strdel(&logs->name);
		free(logs);

		logs = next;
	}
}

void		print_logs(t_child *child)
{
	float	total_cpu_time = 0.0;
	int		total_calls = 0;
	int		total_errors = 0;

	printf("\n%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", "% time", "seconds", "usecs/call",
	 "calls", "errors", "syscall");
	 printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", "______", "_______", "__________",
 	 "______", "______", "________");
	for (t_syscall *logs = child->logs; logs != NULL; logs = logs->next) {
		printf("%f\t%f\t%d\t\t\t%d\t\t%d\t\t%s\n", 0.00, logs->cpu_time, 0, logs->calls, logs->errors, logs->name);
		total_errors += logs->errors;
		total_calls += logs->calls;
	}

	printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n", "______", "_______", "__________",
	"______", "______", "________");

	printf("%f\t%f\t%d\t\t\t%d\t\t%d\t\t%s\n", 100.00, 0.0, 0,
	 total_calls, total_errors, "total");
	free_logs(child);
}
