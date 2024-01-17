/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_manda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:41:24 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/17 16:40:42 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include <fcntl.h>
#include <stdio.h>

void	child_process(t_pipex *p, int pipe_fd[2], int fd[2], char **envp)
{
	p->tmp = found_cmd(envp, p->cmd1[0]);
	if (p->tmp)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(fd[0]);
		close(pipe_fd[1]);
		p->exec = execve(p->tmp, p->cmd1, envp);
		if (p->exec == -1)
			handle_error(p, "Error --> execve", p->cmd2[0], 126);
		free_end(p, 127);
	}
	else
	{
		handle_error(p, "pipex: command not found: ", p->cmd1[0], 127);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		close(fd[0]);
		close(fd[1]);
		free_end(p, 127);
	}
}

void	parent_process(t_pipex *p, int pipe_fd[2], int fd[2], char **envp)
{
	p->tmp = found_cmd(envp, p->cmd2[0]);
	if (p->tmp)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		close(pipe_fd[0]);
		p->exec = execve(p->tmp, p->cmd2, envp);
		if (p->exec == -1)
			handle_error(p, "Error --> execve", p->cmd2[0], 126);
		free_end(p, 127);
	}
	else
	{
		handle_error(p, "pipex: command not found: %s\n", p->cmd2[0], 127);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		close(fd[0]);
		close(fd[1]);
		free_end(p, 127);
	}
}

void	pipex(t_pipex *p, char **argv, char **envp)
{
	int	pipe_fd[2];
	int	fd[2];
	int	pid;

	p->cmd1 = ft_split(argv[2], ' ');
	p->cmd2 = ft_split(argv[3], ' ');
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd[0] < 0 || fd[1] < 0)
		free_end(p, 1);
	if (pipe(pipe_fd) < 0)
		free_end(p, 1);
	pid = fork();
	if (pid < 0)
		free_end(p, 1);
	if (pid == 0)
		child_process(p, pipe_fd, fd, envp);
	else
		parent_process(p, pipe_fd, fd, envp);
	close(fd[0]);
	close(fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	init(&p);
	if (argc != 5 || check_argv(argv) > 0)
	{
		if (check_argv(argv) == 2)
			handle_error(&p, "", argv[1], 1);
		handle_error(&p, "Usage: ./pipex file1 cmd1 cmd2 file2\n", "", 2);
		return (0);
	}
	else
	{
		pipex(&p, argv, envp);
		free_end(&p, 0);
	}
	return (0);
}
