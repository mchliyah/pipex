/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:08:31 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/23 17:30:49 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	free_prnt(t_pb *p)
{
	int	i;

	i = 0;
	close(p->fd_in);
	close(p->fd_out);
	if (p->here_doc)
		unlink(TMP_FILE);
	while (p->c_pths[i])
	{
		free(p->c_pths[i]);
		i++;
	}
	free(p->c_pths);
	free(p->pipe);
}

void	child_free(t_pb *p)
{
	int	i;

	i = 0;
	while (p->args[i])
	{
		free(p->args[i]);
		i++;
	}
	free(p->args);
	free(p->cmd);
}

void	pipe_free(t_pb *p)
{
	close(p->fd_in);
	close(p->fd_out);
	if (p->here_doc)
		unlink(TMP_FILE);
	free(p->pipe);
	write_msg(ERR_ENVP);
	exit(1);
}
