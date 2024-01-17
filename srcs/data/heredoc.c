/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 00:26:04 by marvin            #+#    #+#             */
/*   Updated: 2024/01/17 00:26:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void heredoc(t_pipex *p, char *end)
{
    char *input;
    int fd[2];
    int pid; 

    if (pipe(fd) == -1)
       handle_error(p,"Error --> pipe", "");
    pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            ft_printf("> ");
            input = get_next_line(0);
            if (ft_strncmp(input, end, ft_strlen(end)) == 0)
            {
                free(input);
                exit(-1);
            }
            write(fd[1], input, ft_strlen(input));
        }
    }
    else
    {
        dup2(fd[0], 0);
        waitpid(pid, NULL, 0);
    }
    close(fd[0]);
    close(fd[1]);
}