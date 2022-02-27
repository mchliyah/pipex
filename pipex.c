/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:05:08 by mchliyah          #+#    #+#             */
/*   Updated: 2022/02/27 22:51:49 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		perror ("pip error");
	pid1 = fork();
	if (pid1 < 0)
		perror ("fork1 error");
	if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		printf("pid1 \n");
		execve("/usr/bin/", "env", NULL);
	}
	pid2 = fork();
	if (pid2 < 0)
		perror ("fork1 error");
	if (pid2 == 0)
	{
		dup2(fd[1], 0);
		close(fd[0]);
		close(fd[1]);
		printf("pid2 \n");
		// execve("path of grep cmd", "grep ??", av[3], NULL);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	waitpid(pid2, NULL, 0);
	// system("leaks pipex");
}
