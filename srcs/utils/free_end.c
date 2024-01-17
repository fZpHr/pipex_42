/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:01:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/17 16:19:47 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	error_status(int status)
{
	if (status == 0)
		exit(0);
	else if (status == 1)
		exit(1);
	else if (status == 127)
		exit(127);
}

void	free_end(t_pipex *p, int status)
{
	int	i;

	i = 0;
	if (p->cmd1 != NULL)
		while (p->cmd1[i])
			free(p->cmd1[i++]);
	i = 0;
	if (p->cmd2)
		while (p->cmd2[i])
			free(p->cmd2[i++]);
	if (p->tmp)
		free(p->tmp);
	if (p->tmp_end)
		free(p->tmp_end);
	if (p->tmp_child)
		free(p->tmp_child);
	if (p->cmd1)
		free(p->cmd1);
	if (p->cmd2)
		free(p->cmd2);
	error_status(status);
}
