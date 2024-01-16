/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:41:24 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/16 19:33:42 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	end(t_pipex *p, char *out, char *cmd, char **envp)
{
	int		fd;
	int		exec;

	fd = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		handle_error(p,"Error --> fd outfile", "");
	dup2(fd, 1);
	close(fd);
	p->tmp_end = found_cmd_bonus(p, envp, cmd);
	if (!p->tmp)
		handle_error(p,"Command not found", cmd);
	p->cmd1 = ft_split(cmd, ' ');
	exec = execve(p->tmp_end, p->cmd1, envp);
	if (exec == -1)
		handle_error(p,"Error --> execve", cmd);
}

void	begin(t_pipex *p, char *in)
{
	int	fd;

	fd = open(in, O_RDONLY);
	if (fd == -1)
		handle_error(p,"Error --> fd infile", "");
	dup2(fd, 0);
	close(fd);
}
void	child_process(t_pipex *p, int fd[2], char **envp, char *cmd)
{
	int	exec;

	exec = 0;
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	p->tmp_child = found_cmd_bonus(p, envp, cmd);
	if (!p->tmp_child)
		handle_error(p,"Command not found ", cmd);
	p->cmd1 = ft_split(cmd, ' ');
	exec = execve(p->tmp_child, p->cmd1, envp);
	if (exec == -1)
		handle_error(p,"Error --> execve", cmd);
}
void	pipex(t_pipex *p, char *cmd, char **envp)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		handle_error(p,"Error --> pipe", "");
	pid = fork();
	if (pid == -1)
		handle_error(p,"Error --> fork", "");
	if (pid == 0)
		child_process(p, fd, envp, cmd);
	else
	{
		close(fd[1]);
		wait(NULL);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex p;

	init(&p);
	i = 2;
	if (argc < 5 || check_argv(argv) > 0)
	{
		handle_error(&p,"Usage: ./pipex *existing file input* cmd1 cmd2 ... *name the file output*\n", argv[1]);
		return (0);
	}
	else
		begin(&p, argv[1]);
	while (i < argc - 2)
		pipex(&p, argv[i++], envp);
	end(&p, argv[argc - 1], argv[argc - 2], envp);
	return (0);
}