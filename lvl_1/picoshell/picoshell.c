/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 16:39:03 by logkoege          #+#    #+#             */
/*   Updated: 2025/08/08 16:39:35 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	picoshell(char **cmds[])
{
	int prev_pipe = -1;
	int pipefd[2];
	int i = 0;
	pid_t pid;

	if (!cmds || !cmds[0])
		return (1);

	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(pipefd) == -1)
		{
			if (prev_pipe != -1)
				close(prev_pipe);
			return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			if (cmds[i + 1])
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			if (prev_pipe != -1)
				close(prev_pipe);
			return (1);
		}

		if (pid == 0)
		{
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, 0);
				close(prev_pipe);
			}
			if (cmds[i + 1])
			{
				dup2(pipefd[1], 1);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		if (prev_pipe != -1)
			close(prev_pipe);
		if (cmds[i + 1])
		{
			close(pipefd[1]);
			prev_pipe = pipefd[0];
		}
		i++;
	}
	if (prev_pipe != -1)
		close(prev_pipe);

	while (wait(NULL) > 0)
		;
	return (0);
}