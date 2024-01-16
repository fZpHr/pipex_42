/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:58:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/16 19:27:56 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	*tmp;
	char	*tmp_child;
	char	*tmp_end;
	int		ac;

}			t_pipex;

void		free_end(t_pipex *p);
void		handle_error(t_pipex *p, char *str, char *argv);
char		*found_cmd_bonus(t_pipex *p, char **envp, char *cmd);
char		*found_cmd(char **envp, char *cmd);
int			check_argv(char **argv);
void		init(t_pipex *p);

#endif