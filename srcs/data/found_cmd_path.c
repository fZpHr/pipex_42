/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:08:12 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/11 17:01:47 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*found_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*found_cmd(char **envp, char *cmd)
{
	char	*path;
	char	**path_split;
	char	*cmd_path;
	int		i;

	i = 0;
	path = found_path(envp);
	if(!path)
		return (NULL);
	path_split = ft_split(path, ':');
	while (path_split[i])
	{
		cmd_path = ft_strjoin(path_split[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		i++;
	}
	return (NULL);
}
