/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:26:04 by hbelle            #+#    #+#             */
/*   Updated: 2024/01/17 16:57:13 by hbelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	infinite_loop(int fd[2], char *end)
{
	char	*input;

	while (1)
	{
		ft_printf("pipe heredoc> ");
		input = get_next_line(0);
		if (ft_strncmp(input, end, ft_strlen(end)) == 0)
		{
			free(input);
			exit(-1);
		}
		write(fd[1], input, ft_strlen(input));
		free(input);
	}
}

void	heredoc(t_pipex *p, char *end)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		handle_error(p, "pipex: error pipe", "", 1);
	pid = fork();
	if (pid == -1)
		handle_error(p, "pipex: error fork", "", 1);
	if (pid == 0)
		infinite_loop(fd, end);
	else
	{
		dup2(fd[0], 0);
		waitpid(pid, NULL, 0);
	}
	close(fd[0]);
	close(fd[1]);
}
