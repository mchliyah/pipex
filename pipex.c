/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:05:08 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/01 19:59:42 by mchliyah         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	int		pid1;
	int		pid2;
	int		infilefd;
	int		outfilefd;
	char	**paths;
	char	**args;
	char	*cmd;

	if (ac != 5)
		return (0);
	infilefd = open(av[1], O_RDONLY);
	// open file to read from
	if (infilefd < 0)
		perror ("infile error");
	outfilefd = open(av[ac - 1], O_CREAT | O_RDWR, 0644);
	 // create a file to write the result in 
	if (pipe(fd) == -1)
		perror ("pip error");
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	paths = ft_split(*envp, ':');
	// commands path from envp
	pid1 = fork();
	  //child 1 created
	if (pid1 < 0)
		perror ("fork1 error");
	if (pid1 == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		dup2(infilefd, 0);
		args = ft_split(av[2], ' ');
		cmd = cmnd(paths, args[0]);
		if (!cmd)
			perror("command not exist");
		execve(cmd, args, envp);
	 // comaand N1 must be executed and the result derected to the pip :) and the shild must be dead :( 
	}
	pid2 = fork();
	 // other child just born now hhhhh
	if (pid2 < 0)
		perror ("fork1 error");
	if (pid2 == 0)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		dup2(outfilefd, 1);
		args = ft_split(av[3], ' ');
		cmd = cmnd(paths, args[0]);
		if (!cmd)
			perror("command not exist");
		execve(cmd, args, envp);
	}
	close(fd[0]);
	close(fd[1]);
	wait(NULL);
	waitpid(pid2, NULL, 0);
	// system("leaks pipex");
}
