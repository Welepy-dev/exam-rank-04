/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:05:35 by welepy            #+#    #+#             */
/*   Updated: 2025/07/08 14:42:24 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	int	fd[2];
	if (pipe(fd) == -1)
		return (-1);
	pid_t pid = fork();
	if (pid < 0)
		return (close(fd[1]), close(fd[0]), -1);
	if (pid == 0)
	{
		if (type == 'r')
			dup2(fd[1], STDOUT_FILENO);
		else 
			dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execvp(file, argv);
		exit(127);
	}
	if (type == 'r')
		return (close(fd[1]), fd[0]);
	else 
		return (close(fd[0]), fd[1]);
}
