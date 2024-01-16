/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 13:58:56 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/16 14:37:21 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	handle_error(t_pipex *p, char *str, char *argv)
{
	ft_putstr_fd("\033[0;31m", 2);
	ft_printf("%s", str);
	perror(argv);
	ft_putstr_fd("\033[0m", 2);
	free_end(p);
	p->cmd1 = NULL;
	exit(-1);
}