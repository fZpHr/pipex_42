/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:41:24 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/12 18:29:11 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	child_process(t_pipex *p, int pipe_fd[2], int fd[2], char **envp)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	p->tmp = found_cmd(envp, p->cmd1[0]);
	if (p->tmp)
		execve(p->tmp, p->cmd1, envp);
	free_end(p);
}

void	parent_process(t_pipex *p, int pipe_fd[2], int fd[2], char **envp)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}

void	pipex(t_pipex *p, char *argv, char **envp)
{
	int		pipe_fd[2];
	int		fd[2];
	pid_t	pid;

	p->cmd1 = ft_split(argv, ' ');
	fd[0] = open(argv, O_RDONLY);
	fd[1] = open(argv[p->ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd[0] < 0 || fd[1] < 0)
		free_end(p);
	if (pipe(pipe_fd) < 0)
		free_end(p);
	pid = fork();
	if (pid < 0)
		free_end(p);
	if (pid == 0)
		child_process(p, pipe_fd, fd, envp);
	else
		parent_process(p, pipe_fd, fd, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		i;

	i = 0;
	p.ac = argc;
	if (argc != 5 || check_argv(argv) > 0)
	{
		if (check_argv(argv) == 2 && argc == 2)
			ft_printf("%s: No such file\n", argv[1]);
		ft_printf("Usage: ./pipex file1 cmd1 cmd2 file2\n");
		return (0);
	}
	else
	{
		while (argv[i] <= argc - 3)
		{
			pipex(&p, argv[i++], envp);
			p.cmd2 = p.cmd1;
		}
		free_end(&p);
	}
	return (0);
}
