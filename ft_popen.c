/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: logkoege <logkoege@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:30:09 by logkoege          #+#    #+#             */
/*   Updated: 2025/08/07 11:32:27 by logkoege         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const av[], char type)
{
	int		fd[2];
	pid_t	pid;

	if (!av || !file || (type != 'w' && type != 'r'))
		return (1);
	if (pipe(fd) < 0)
		return (1);
	pid = fork();
	if(pid < 0)
	{
		close(fd[1]);
		close(fd[0]);
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
		close(fd[0]);
		close(fd[1]);
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
