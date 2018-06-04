/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:59:38 by frmarinh          #+#    #+#             */
/*   Updated: 2018/05/26 16:00:05 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

# define PTRACE_EVENT_STOP      128

long reg_from_position(struct user_regs_struct *regs, int arg)
{
    switch (arg) {
        case 0:
            return regs->rdi;
            break;
        case 1:
            return regs->rsi;
            break;
        case 2:
            return regs->rdx;
            break;
        case 3:
            return regs->r10;
            break;
        case 4:
            return regs->r8;
            break;
        case 5:
            return regs->r9;
            break;
    }
    return -1;
}

char        *read_string(pid_t pid, long registery_address)
{
    char *val = NULL;

    if (!(val = (char*)malloc(sizeof(char) * BUFFER_SIZE)))
        return (NULL);

    memset(val, 0, (BUFFER_SIZE - 1));
    int allocated = BUFFER_SIZE, read = 0;
    unsigned long tmp = 0;
    while (1)
    {
        if (read + sizeof tmp > allocated) {
            allocated *= 2;
            val = realloc(val, allocated);
        }

       tmp = ptrace(PTRACE_PEEKDATA, pid, registery_address + read);
       memcpy(val + read, &tmp, sizeof tmp);
       if (memchr(&tmp, 0, sizeof tmp) != NULL) {
            break;
        }
        read += sizeof tmp;
    }
    if (strlen(val) > 0) {
        return val;
    } else {
        free(val);
        return NULL;
    }
}

void		do_trace(t_child *child)
{
	int                        status;
	struct user_regs_struct    regs;
	char                       child_content[BUFFER_SIZE];

    bool    in_syscall              = true;
    bool    stopped                 = false;
    int     syscall_n               = 0;
    char    *syscall_name           = NULL;
    char    *args                   = NULL;
    bool    infos_flag              = flag_active(INFOS_FLAG);


    g_child = child;
	memset((char*)&child_content, 0, (BUFFER_SIZE - 1));
	ptrace(PTRACE_SEIZE, child->pid, NULL, NULL);

	ptrace(PTRACE_INTERRUPT, child->pid, NULL, NULL);
	ptrace(PTRACE_SETOPTIONS, child->pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		wait( &status );
      	if (WIFEXITED(status)) {
            strdel(&args);
            if (!infos_flag) {
                fprintf(stderr, " => ?\n+++ exited with %d +++\n", WEXITSTATUS(status));
            }
			break;
		}
        int sig = WSTOPSIG(status);
        if (sig == 0) {
            break;
        }

        if (WIFSTOPPED(status) && sig == SIGCHLD) {
            ptrace(PTRACE_SYSCALL, child->pid, 0, SIGCHLD); // send SIGCHLD to the bastard to avoid zombie process
            continue;
        } else if (sig == SIGINT) {
            printf("ft_strace: Process %d detached\n", child->pid);
            ptrace(PTRACE_SYSCALL, child->pid, 0, SIGINT);
            ptrace(PTRACE_DETACH, child->pid, 0);
            continue;
        }

		if (WIFSTOPPED(status) && sig == SIGTRAP) {
			ptrace( PTRACE_GETREGS, child->pid, 0, &regs );

    		if (!in_syscall) {
                syscall_n = regs.orig_rax;
                syscall_name = get_syscall_name(syscall_n);
                args = get_syscall_args(syscall_n, &regs, child);
                if (!infos_flag) {
                    fprintf(stderr, "%s(%s)", syscall_name, args);
                }
                in_syscall = true;
    		} else {
    			ptrace(PTRACE_GETREGS, child->pid, 0, &regs);
    			in_syscall = false;
    		}

            if (!in_syscall && syscall_name) {
                bool error_found = false;
                long int possible_error = (long int)regs.rax;
                if (possible_error < 0) {
                    char *error_type = get_errno_error(-possible_error);
                    if (error_type != NULL) {
                        char *error = strerror(-possible_error);
                        if (strcmp(error, SUCCESS_ERRNO_MSG)) {
                            if (!infos_flag) {
                                fprintf(stderr, " => -1 %s (%s)\n", error, error_type);
                            } else {
                                add_log(child, syscall_n, syscall_name, true, 0.0);
                            }
                            error_found = true;
                        }
                    }
                }
                if (!error_found) {
                    char *ret = get_syscall_return(syscall_n, &regs);
                    if (!infos_flag) {
                        fprintf(stderr, " => %s\n", ret);
                    } else {
                        add_log(child, syscall_n, syscall_name, false, 0.0);
                    }
                    strdel(&ret);
                }
                strdel(&args);
            }
		}
		ptrace(PTRACE_SYSCALL, child->pid, 0, 0);
	}

    if (flag_active(INFOS_FLAG)) {
        print_logs(child);
    }
}
