/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:08:31 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/18 19:59:10 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	parent_free(t_ppxb *p)
{
	int	i;

	i = 0;
	close(p->fd_in);
	close(p->fd_out);
	// if (p->here_doc)
	// 	unlink(".heredoc_tmp");
	while (p->cmd_paths[i])
	{
		free(p->cmd_paths[i]);
		i++;
	}
	free(p->cmd_paths);
	free(p->pipe);
}

void	child_free(t_ppxb *p)
{
	int	i;

	i = 0;
	while (p->cmd_args[i])
	{
		free(p->cmd_args[i]);
		i++;
	}
	free(p->cmd_args);
	free(p->cmd);
}

void	pipe_free(t_ppxb *p)
{
	close(p->fd_in);
	close(p->fd_out);
	// if (p->here_doc)
	// 	unlink(".heredoc_tmp");
	free(p->pipe);
	msg(ERR_ENVP);
	exit(1);
}
