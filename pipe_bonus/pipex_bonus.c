/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:13:29 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/19 23:49:55 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	creat_pipes(t_pb *p)
{
	int	i;

	i = 0;
	while (i < p->c_nbr - 1)
	{
		if (pipe(p->pipe + 2 * i) < 0)
			parent_free(p);
		i++;
	}
}

void	close_pipes(t_pb *p)
{
	int	i;

	i = 0;
	while (i < (p->pipe_nb))
	{
		close(p->pipe[i]);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pb	p;

	if (ac < args_in(av[1], &p))
		return (msg(ERR_INPUT));
	get_infile(av, &p);
	get_outfile(av[ac - 1], &p);
	p.c_nbr = ac - 3;
	p.pipe_nb = 2 * (p.c_nbr - 1);
	p.pipe = (int *)malloc(sizeof(int) * p.pipe_nb);
	if (!p.pipe)
		msg_error(ERR_PIPE);
	p.path = find_path(envp);
	p.c_pths = ft_split(p.path, ':');
	creat_pipes(&p);
	p.idx = -1;
	while (++(p.idx) < p.c_nbr)
		child(p, av, envp);
	waitpid(-1, NULL, 0);
	return (0);
}
