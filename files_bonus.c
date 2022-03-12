/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:08:15 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/12 14:15:44 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	get_infile(char **argv, t_ppxb *pipex)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		here_doc(argv[2], pipex);
	else
	{
		pipex->fd_in = open(argv[1], O_RDONLY);
		if (pipex->fd_in < 0)
			msg_error(ERR_INFILE);
	}
}

void	get_outfile(char *argv, t_ppxb *pipex)
{
	if (pipex->here_doc)
		pipex->fd_out = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		pipex->fd_out = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex->fd_out < 0)
		msg_error(ERR_OUTFILE);
}
