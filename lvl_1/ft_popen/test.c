/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:51:07 by logkoege          #+#    #+#             */
/*   Updated: 2025/08/11 12:51:08 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_popen(const char *file, char *const av[], char type)
{
	int fd[2];
	pid_t pid;

	if (!av || !file || (type != 'r' && type != 'w'))
		return (1);
	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		close(fd[1]);
		close(fd[0]);
		exit(1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
		}
		close(fd[1]);
		close(fd[0]);
		execvp(file, av);
		exit(1);
	}
	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	close(fd[0]);
	return (fd[1]);
}