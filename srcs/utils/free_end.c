/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 16:01:42 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/12 14:37:42 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	free_end(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->cmd1[i])
		free(p->cmd1[i++]);
	i = 0;
	while (p->cmd2[i])
		free(p->cmd2[i++]);
	if (p->tmp)
		free(p->tmp);
	if (p->cmd1)
		free(p->cmd1);
	if (p->cmd2)
		free(p->cmd2);
	exit(0);
}
