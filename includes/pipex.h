/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:58:21 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/17 16:40:01 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <error.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	*tmp;
	char	*tmp_child;
	char	*tmp_end;
	int		exec;
	int		ac;

}			t_pipex;

void		free_end(t_pipex *p, int status);
void		handle_error(t_pipex *p, char *str, char *argv, int status);
char		*found_cmd_bonus(t_pipex *p, char **envp, char *cmd);
char		*found_cmd(char **envp, char *cmd);
int			check_argv(char **argv);
void		init(t_pipex *p);
void		heredoc(t_pipex *p, char *end);

#endif