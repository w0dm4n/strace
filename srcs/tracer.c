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

void
getdata(pid_t child, long addr,char *str, int len)
{
    char *laddr;
    int i, j;

    union u
    {
            long val;
            char chars[sizeof(long)];
    }data;

    i = 0;
    j = len / sizeof(long);
    laddr = str;

    while(i < j)
    {
        if((data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * 4, NULL)) == -1)
		perror("PTRACE_PEEKDATA failed.");
        memcpy(laddr, data.chars, sizeof(long));
        ++i;
        laddr += sizeof(long);
    }

    j = len % sizeof(long);

    if(j != 0)
    {
        if((data.val = ptrace(PTRACE_PEEKDATA, child, addr + i * 4, NULL)) == -1)
		perror("PTRACE_PEEKDATA failed.");
        memcpy(laddr, data.chars, j);
    }

    str[len] = '\0';
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

	memset((char*)&child_content, 0, 1023);
	ptrace(PTRACE_SEIZE, child->pid, NULL, NULL);

	ptrace(PTRACE_INTERRUPT, child->pid, NULL, NULL);
	ptrace(PTRACE_SETOPTIONS, child->pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		wait( &status );
		event = ((unsigned)status >> 16);
      	if ( WIFEXITED( status ) ) {
			printf("Child is dead !\n");
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
					printf("Stopped !\n");
					stopped = 1;
					//goto show_stopsig;
				}
			}

		if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
			ptrace( PTRACE_GETREGS, child->pid, 0, &regs );
	      	syscall_n = regs.orig_rax;
			if (!in_syscall) {
				printf("New syscall %d\n", syscall_n);
				in_syscall = true;
			} else {
				ptrace( PTRACE_GETREGS, child->pid, 0, &regs );
				printf(" ret %d\n\n", regs.rdx);
				in_syscall = false;
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
