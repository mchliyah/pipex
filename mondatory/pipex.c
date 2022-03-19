/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:05:08 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/19 21:25:57 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_p	*get_path(t_p *pip, char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	pip->paths = ft_split(*envp + 5, ':');
	return (pip);
}

t_p	*get_files(t_p *pip, int ac, char **av)
{
	pip->fd_in = open(av[1], O_RDONLY);
	if (pip->fd_in < 0)
		perror ("infile error");
	pip->fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipe(pip->fd) == -1)
		perror ("pip error");
	return (pip);
}

int	main(int ac, char **av, char **envp)
{
	t_p	*pip;

	pip = malloc(sizeof(t_p));
	if (ac != 5)
	{
		perror("argument error");
		return (0);
	}
	pip = get_files(&pip, ac, av);
	pip = get_path(&pip, envp);
	pip->pid1 = fork();
	if (pip->pid1 < 0)
		perror ("fork1 error");
	pip = cmd_1(&pip, av, envp);
	pip->pid2 = fork();
	if (pip->pid2 < 0)
		perror ("fork1 error");
	pip = cmd_2(&pip, av, envp);
	close(&pip->fd[0]);
	close(&pip->fd[1]);
	wait(NULL);
	wait(NULL);
	return (1);
}
