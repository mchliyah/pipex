/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:05:08 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/06 15:21:37 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*cmnd(char **path, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		path++;
	}
	return (NULL);
}

t_p get_path(t_p pip, char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	pip.paths = ft_split(*envp, ':');
	return (pip);
}
t_p cmd_1(t_p pip, char **av, char **envp)
{
	if (pip.pid1 == 0)
	{
		dup2(pip.fd[1], 1);
		close(pip.fd[0]);
		dup2(pip.infilefd, 0);
		pip.args = ft_split(av[2], ' ');
		pip.cmd = cmnd(pip.paths, pip.args[0]);
		if (!pip.cmd)
			perror("command not exist");
		execve(pip.cmd, pip.args, envp);
	}
	return (pip);
}

t_p cmd_2(t_p pip, char **av, char **envp)
{
	if (pip.pid2 == 0)
	{
		dup2(pip.fd[0], 0);
		close(pip.fd[1]);
		dup2(pip.outfilefd, 1);
		pip.args = ft_split(av[3], ' ');
		pip.cmd = cmnd(pip.paths, pip.args[0]);
		if (!pip.cmd)
			perror("command not exist");
		execve(pip.cmd, pip.args, envp);
	}
	return (pip);
}

int	main(int ac, char **av, char **envp)
{
	t_p	pip;

	if (ac != 5)
		return (0);
	pip.infilefd = open(av[1], O_RDONLY);
	if (pip.infilefd < 0)
		perror ("infile error");
	pip.outfilefd = open(av[ac - 1], O_CREAT | O_RDWR, 0777);
	if (pipe(pip.fd) == -1)
		perror ("pip error");
	pip = get_path(pip, envp);
	pip.pid1 = fork();
	if (pip.pid1 < 0)
		perror ("fork1 error");
	pip = cmd_1(pip, av, envp);
	pip.pid2 = fork();
	if (pip.pid2 < 0)
		perror ("fork1 error");
	pip = cmd_2(pip, av, envp);
	close(pip.fd[0]);
	close(pip.fd[1]);
	wait(NULL);
}
