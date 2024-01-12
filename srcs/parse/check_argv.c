/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:57:54 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/12 17:08:36 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	check_argv(char **argv)
{
	if (access(argv[1], F_OK | R_OK) == 0)
		return (0);
	else
		return (2);
	return (1);
}
