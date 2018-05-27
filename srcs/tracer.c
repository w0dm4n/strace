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
	bool in_syscall = false;

	memset((char*)&child_content, 0, 1023);
	ptrace(PTRACE_SEIZE, child->pid, NULL, NULL);
	// ptrace(PTRACE_SINGLESTEP,
	// 	  child->pid, NULL, NULL);
	ptrace(PTRACE_INTERRUPT, child->pid, NULL, NULL);
	// ptrace(PTRACE_SETOPTIONS, child->pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		int res = wait(&status);
		if (res < 0 || WIFEXITED(child->pid)) {
			printf("Child is dead !\n");
			break;
		}
		ptrace(PTRACE_INTERRUPT,
			  child->pid, NULL, NULL);
		if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
			if (!in_syscall) {
				in_syscall = true;
				if (!ptrace(PTRACE_GETREGS, child->pid, &regs, &regs)) {
					if (regs.orig_rax == 1) {
						getdata(child->pid,ptrace_argument(child->pid, 1),child_content,1023);
						// char *lol = read_string(child->pid, regs.rax);
						printf("THE CHILD MADE ONE WRITE ! %s (%p)\n", child_content, regs.orig_rax);
					}
				}
			} else {
					if (regs.orig_rax == 1) {
				printf("End of syscall %d\n", regs.orig_rax);}
				in_syscall = false;
				ptrace(PTRACE_SYSCALL, child->pid, NULL, NULL);
			}
		} else
		{
			//printf("Issou: %d\n", WSTOPSIG(status));
		}
        //
		// long syscall = ptrace(PTRACE_PEEKUSER, child->pid, sizeof(long)*ORIG_RAX);


		// printf("Hello %s (%d)\n", strerror(errno), res);
		// printf("Syscall made: %d\n", syscall);


		ptrace(PTRACE_CONT,
			  child->pid, NULL, NULL);
		ptrace(PTRACE_SYSCALL, child->pid, NULL, NULL);
	}
}
