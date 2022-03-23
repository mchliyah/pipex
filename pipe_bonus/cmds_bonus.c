/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:10:00 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/23 18:18:42 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static void	fd_dup2(int zero, int first)
{
	dup2(zero, 0);
	dup2(first, 1);
}

void	child(t_pb p, char **argv, char **envp)
{
	p.pid = fork();
	if (!p.pid)
	{
		if (p.pidx == 0)
			fd_dup2(p.fd_in, p.pipe[1]);
		else if (p.pidx == p.c_nbr - 1)
			fd_dup2(p.pipe[2 * p.pidx - 2], p.fd_out);
		else
			fd_dup2(p.pipe[2 * p.pidx - 2], p.pipe[2 * p.pidx + 1]);
		close_pipes(&p);
		p.args = ft_split(argv[2 + p.here_doc + p.pidx], ' ');
		p.cmd = get_cmd(p.c_pths, p.args[0]);
		if (!p.cmd)
		{
			pipe_msg(p.args[0]);
			child_free(&p);
			exit(1);
		}
		execve(p.cmd, p.args, envp);
	}
	err_msg(ERR_FORK);
}
