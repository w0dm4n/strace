/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 18:27:22 by frmarinh          #+#    #+#             */
/*   Updated: 2018/05/26 18:27:29 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	get_error(bool exit_program)
{
	printf("ft_strace inform you that a nasty error occured: %s\n", strerror(errno));
	if (exit_program) {
		exit(-1);
	}
}
