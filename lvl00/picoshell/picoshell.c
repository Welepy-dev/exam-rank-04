/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picoshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:32:53 by welepy            #+#    #+#             */
/*   Updated: 2025/07/08 15:35:00 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int i = 0;
	int fd[2];
	int prev_read = -1;
	pid_t pid;

	while (cmds[i])
	{
		if (cmds[i + 1])
			if (pipe(fd) == -1)
				return 1;

		pid = fork();
		if (pid == -1)
			return 1;

		if (pid == 0)
		{
			// Child process
			if (prev_read != -1)
			{
				dup2(prev_read, STDIN_FILENO);
				close(prev_read);
			}
			if (cmds[i + 1])
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1); // exec failed
		}
		// Parent process
		if (prev_read != -1)
			close(prev_read);
		if (cmds[i + 1])
		{
			close(fd[1]);
			prev_read = fd[0];
		}
		i++;
	}
	// Wait for all child processes
	int status;
	while (i-- > 0)
		wait(&status);
	return 0;
}

/*int main(void) {
	char *cmd1[] = {"ls", NULL};
	char *cmd2[] = {"grep", ".c", NULL};
	char *cmd3[] = {"wc", "-l", NULL};
	char **cmds[] = {cmd1, cmd2, cmd3, NULL};

	if (picoshell(cmds) == 1)
		write(2, "Command failed\n", 15);
	return 0;
}*/

