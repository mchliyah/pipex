/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:08:15 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/21 00:58:56 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	get_infile(char **av, t_pb *p)
{
	if (!ft_strcmp("here_doc", av[1]))
		here_doc(av, p);
	else
		p->fd_in = open(av[1], O_RDONLY);
	if (p->fd_in < 0)
		msg_error(ERR_INFILE);
}

void	get_outfile(char *av, t_pb *p)
{
	p->fd_out = open(av, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->fd_out < 0)
		msg_error(ERR_OUTFILE);
}
