/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:58:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/12 14:59:40 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	*tmp;
	char	*path;
	char	**path_split;
	char	*cmd_path;
	char	*cmd_path_tmp;
	int		i;

}			t_pipex;

void		free_end(t_pipex *p);
char		*found_cmd(char **envp, char *cmd);
int			check_argv(char **argv);

#endif