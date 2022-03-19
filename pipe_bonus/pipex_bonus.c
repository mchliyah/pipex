/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:13:29 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/19 22:13:22 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	creat_pipes(t_ppxb *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_nmbs - 1)
	{
		if (pipe(p->pipe + 2 * i) < 0)
			parent_free(p);
		i++;
	}
}

void	close_pipes(t_ppxb *p)
{
	int	i;

	i = 0;
	while (i < (p->pipe_nmbs))
	{
		close(p->pipe[i]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_ppxb	p;

	// if (ac < args_in(av[1], &pipex))
	// 	return (msg(ERR_INPUT));
	get_infile(av, &p);
	get_outfile(av[ac - 1], &p);
	p.cmd_nmbs = ac - 3;
	p.pipe_nmbs = 2 * (p.cmd_nmbs - 1);
	p.pipe = (int *)malloc(sizeof(int) * p.pipe_nmbs);
	if (!p.pipe)
		msg_error(ERR_PIPE);
	p.env_path = find_path(envp);
	p.cmd_paths = ft_split(p.env_path, ':');
	creat_pipes(&p);
	p.idx = -1;
	while (++(p.idx) < p.cmd_nmbs)
		child(p, av, envp);
	waitpid(-1, NULL, 0);
	return (0);
}
