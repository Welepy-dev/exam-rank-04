/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_popen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welepy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:05:35 by welepy            #+#    #+#             */
/*   Updated: 2025/07/08 14:51:05 by welepy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
/*
// Prototype of ft_popen
int ft_popen(const char *file, char *const argv[], char type);

// Dummy version of get_next_line and ft_putstr for demonstration
char *get_next_line(int fd) {
    static char buffer[1024];
    ssize_t n = read(fd, buffer, sizeof(buffer) - 1);
    if (n <= 0)
        return NULL;
    buffer[n] = '\0';
    return buffer;
}

void ft_putstr(const char *s) {
    write(1, s, strlen(s));
}

int main(void)
{
    // Launch "ls" command, capturing its output
    int fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');
    if (fd == -1)
    {
        perror("ft_popen failed");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)))
        ft_putstr(line);

    close(fd);
    return 0;
}
*/
