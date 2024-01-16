/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:36:39 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/16 19:29:47 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	init(t_pipex *p)
{
	p->cmd1 = NULL;
	p->cmd2 = NULL;
	p->envp = NULL;
	p->tmp = NULL;
	p->ac = 0;
	p->tmp_end = NULL;
	p->tmp_child = NULL;
}