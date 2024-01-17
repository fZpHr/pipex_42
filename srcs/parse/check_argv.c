/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:57:54 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/16 18:22:33 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	check_argv(char **argv)
{
	if (argv[1])
	{
		if (access(argv[1], F_OK | R_OK) == 0 || ft_strncmp(argv[1], "here_doc", 8) == 0)
			return (0);
		else
			return (2);
	}
	return (1);
}
