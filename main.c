/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:41:24 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/11 17:58:46 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"
#include <fcntl.h>
#include <stdio.h>

void	pipex(t_pipex *p, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		fd[2];
	pid_t	pid;

	//>> O_APPEND
	p->cmd1 = ft_split(argv[2], ' ');
	p->cmd2 = ft_split(argv[3], ' ');
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd[0] < 0 || fd[1] == -1)
		free_end(p);
	if (pipe(pipe_fd) == -1)
		free_end(p);
	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		p->tmp = found_cmd(envp, p->cmd1[0]);
		execve(p->tmp, p->cmd1, envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		p->tmp = found_cmd(envp, p->cmd1[0]);
		execve(p->tmp, p->cmd2, envp);
		exit(EXIT_FAILURE);
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		i;

	i = 1;
	if (argc != 5)
		return (0);
	else
	{
		while (i <= argc - 3)
			pipex(&p, argv[i++], envp);
		free_end(&p);
	}
	return (0);
}
