/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:57:54 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/12 15:36:59 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

int	check_argv(char **argv)
{
	char tmp[6] = "file1";
	char tmp2[6] = "file2";

	if ((ft_strcmp(argv[1], tmp) == 0) && (ft_strcmp(argv[4], tmp2) == 0))
		return (0);
	else
		return (1);
}