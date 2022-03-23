/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:08:15 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/23 22:59:37 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*find_path(char **env)
{
	while (ft_strncmp("PATH=", *env, 4))
	{
		if (ft_strncmp("PATH=", *env, 4) == -1)
			err_msg(ERR_CMD);
		env++;
	}
	return (*env + 5);
}

void	get_infile(char **av, t_pb *p)
{
	if (!ft_strcmp("here_doc", av[1]))
		here_doc(av, p);
	else
		p->fd_in = open(av[1], O_RDONLY);
	if (p->fd_in < 0)
		err_msg(ERR_INFILE);
}

void	get_outfile(char *av, t_pb *p)
{
	p->fd_out = open(av, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->fd_out < 0)
		err_msg(ERR_OUTFILE);
}
