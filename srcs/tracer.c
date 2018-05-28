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

long ptrace_argument(pid_t pid, int arg)
{
    int reg = 0;
    switch (arg) {
        /* %rdi, %rsi, %rdx, %rcx, %r8 and %r9 */
        case 0:
            reg = RDI;
            break;
        case 1:
            reg = RSI;
            break;
        case 2:
            reg = RDX;
            break;
        case 3:
            reg = R10;
            break;
        case 4:
            reg = R8;
            break;
        case 5:
            reg = R9;
            break;
    }

    return ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * reg, NULL);
}

/*
** PTRACE_O_TRACESYSGOOD means that when the child stops for a syscall-related reason,
** we’ll actually see it stopped with signal number
*/

char        *read_string(pid_t pid, long registery_address)
{
    char *val = NULL;

    if (!(val = (char*)malloc(sizeof(char) * 1024)))
        return (NULL);

    memset(val, 0, 1023);
    int allocated = 1024, read = 0;
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
	int status;
	struct user_regs_struct regs;
	char child_content[1024];
	bool in_syscall = true;
	int syscall_n = 0;
	unsigned event;
	bool stopped = false;
    char *syscall_name = NULL;
    char *args = NULL;

	memset((char*)&child_content, 0, 1023);
	ptrace(PTRACE_SEIZE, child->pid, NULL, NULL);

	ptrace(PTRACE_INTERRUPT, child->pid, NULL, NULL);
	// ptrace(PTRACE_SETOPTIONS, child->pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		wait( &status );
		event = ((unsigned)status >> 16);
      	if ( WIFEXITED( status ) ) {
            args = print_syscall_args(syscall_n, &regs, child);
            printf("%s(%s)\n", syscall_name, args);
            strdel(&args);
			break;
		}

		int sig = WSTOPSIG(status);
		if (event == PTRACE_EVENT_STOP) {
				/*
				 * PTRACE_INTERRUPT-stop or group-stop.
				 * PTRACE_INTERRUPT-stop has sig == SIGTRAP here.
				 */
				if (sig == SIGSTOP
				 || sig == SIGTSTP
				 || sig == SIGTTIN
				 || sig == SIGTTOU
				) {
					stopped = 1;
				}
			}

		if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
			ptrace( PTRACE_GETREGS, child->pid, 0, &regs );
	      	syscall_n = regs.orig_rax;

    		if (!in_syscall) {
                syscall_name = get_syscall_name(syscall_n);
                args = print_syscall_args(syscall_n, &regs, child);
                printf("%s(%s)", syscall_name, args);
                in_syscall = true;
    		} else {
    			ptrace(PTRACE_GETREGS, child->pid, 0, &regs);
    			in_syscall = false;
    		}

            if (!in_syscall && syscall_name) {
                bool error_found = false;
                long int possible_error = (long int)regs.rax;
                if (possible_error < 0) {
                    char *error = strerror(-possible_error);
                    if (strcmp(error, SUCCESS_ERRNO_MSG)) {
                        printf(" => -1 %s\n", error);
                        error_found = true;
                    }
                }
                if (!error_found) {
                    printf(" => %d\n", regs.rax);
                }
                strdel(&args);
            }
		}

		if (!stopped) {
			ptrace( PTRACE_SYSCALL, child->pid, 0, 0 );
		} else {
			ptrace(PTRACE_LISTEN,
				  child->pid, NULL, NULL);
		}
	}
}
