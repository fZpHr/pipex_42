/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 13:41:24 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/17 15:31:07 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	end(t_pipex *p, char *out, char *cmd, char **envp)
{
	int	fd;
	int	exec;

	fd = open(out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		handle_error(p, "Error --> fd outfile", "");
	p->tmp_end = found_cmd_bonus(p, envp, cmd);
	if (!p->tmp_end)
		handle_error(p, "Command not found --> ", cmd);
	dup2(fd, 1);
	close(fd);
	p->cmd1 = ft_split(cmd, ' ');
	exec = execve(p->tmp_end, p->cmd1, envp);
	if (exec == -1)
		handle_error(p, "Error --> execve", cmd);
}

void	begin(t_pipex *p, char *in)
{
	int	fd;

	fd = open(in, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		handle_error(p, "Error --> fd infile", "");
	}
	dup2(fd, 0);
	close(fd);
}

void	child_process(t_pipex *p, int fd[2], char **envp, char *cmd)
{
	int	exec;

	exec = 0;
	p->tmp_child = found_cmd_bonus(p, envp, cmd);
	if (!p->tmp_child)
	{
		close(fd[1]);
		close(fd[0]);
		handle_error(p, "Command not found --> ", cmd);
	}
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	p->cmd1 = ft_split(cmd, ' ');
	exec = execve(p->tmp_child, p->cmd1, envp);
	if (exec == -1)
		handle_error(p, "Error --> execve", cmd);
}

void	pipex(t_pipex *p, char *cmd, char **envp)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		handle_error(p, "Error --> pipe", "");
	}
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		handle_error(p, "Error --> fork", "");
	}
	if (pid == 0)
		child_process(p, fd, envp, cmd);
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	p;

	init(&p);
	i = 2;
	if (argc < 5 || check_argv(argv) > 0)
	{
		handle_error(&p,
			"Usage: ./pipex *existing file* cmd1 cmd2 ... *name the file*\n",
			argv[1]);
		return (0);
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		heredoc(&p, argv[2]);
	}
	else
		begin(&p, argv[1]);
	while (i < argc - 2)
		pipex(&p, argv[i++], envp);
	end(&p, argv[argc - 1], argv[argc - 2], envp);
	return (0);
}
