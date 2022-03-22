/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:13:29 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/22 02:06:56 by mchliyah         ###   ########.fr       */
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
		{
			parent_free(p);
			perror(ERR_PIPE);
			exit(1);
		}
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

void	get_files(int ac, char **av, t_pb *p)
{
	get_infile(av, p);
	get_outfile(av[ac - 1], p);
	if (!p->here_doc)
		p->c_nbr = ac - 3;
	else
		p->c_nbr = ac - 4;
}

int	main(int ac, char **av, char **envp)
{
	t_pb	p;

	p.wt_nb = 0;
	if (ac < args_in(av[1], &p))
		return (msg(ERR_INPUT));
	get_files(ac, av, &p);
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
	close_pipes(&p);
	parent_free(&p);
	while (p.wt_nb++ < p.pipe_nb)
		wait(NULL);
	return (0);
}
