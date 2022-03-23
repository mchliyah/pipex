/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:05:08 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/23 22:55:39 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

t_p	*get_path(t_p *pip, char **env)
{
	while (ft_strncmp("PATH=", *env, 4))
	{
		if (ft_strncmp("PATH=", *env, 4) == -1)
			err_msg(ERR_CMD);
		env++;
	}
	pip->paths = ft_split(*env + 5, ':');
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

int	main(int ac, char **av, char **env)
{
	t_p	*pip;

	pip = malloc(sizeof(t_p));
	if (ac != 5)
		return (write_msg(ERR_INPUT));
	pip = get_files(pip, ac, av);
	pip = get_path(pip, env);
	pip->pid1 = fork();
	if (pip->pid1 < 0)
		err_msg("fork1 error");
	pip = cmd_1(pip, av, env);
	pip->pid2 = fork();
	if (pip->pid2 < 0)
		err_msg("fork1 error");
	pip = cmd_2(pip, av, env);
	close(pip->fd[0]);
	close(pip->fd[1]);
	wait(NULL);
	wait(NULL);
	return (1);
}
