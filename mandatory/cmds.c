/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <mchliyah@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 23:09:20 by mchliyah          #+#    #+#             */
/*   Updated: 2023/01/16 21:54:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*cmnd(char **path, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		path++;
	}
	return (NULL);
}

t_p	*cmd_1(t_p *pip, char **av, char **envp)
{
	if (pip->pid1 == 0)
	{
		close(pip->fd[0]);
		dup2(pip->fd_in, 0);
		dup2(pip->fd[1], 1);
		pip->args = ft_split(av[2], ' ');
		if (access(*pip->args, X_OK) == 0)
			execve(*pip->args, pip->args, envp);
		else
		{
			pip->cmd = cmnd(pip->paths, pip->args[0]);
			if (pip->cmd)
				execve(pip->cmd, pip->args, envp);
			pipe_msg(pip->args[0]);
			exit(1);
		}
	}
	return (pip);
}

t_p	*cmd_2(t_p *pip, char **av, char **envp)
{
	if (pip->pid2 == 0)
	{
		dup2(pip->fd[0], 0);
		close(pip->fd[1]);
		dup2(pip->fd_out, 1);
		pip->args = ft_split(av[3], ' ');
		if (access(*pip->args, X_OK) == 0)
			execve(*pip->args, pip->args, envp);
		else
		{
			pip->cmd = cmnd(pip->paths, pip->args[0]);
			if (pip->cmd)
				execve(pip->cmd, pip->args, envp);
			pipe_msg(pip->args[0]);
			exit(1);
		}
	}
	return (pip);
}
