/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:08:41 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/23 18:18:42 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	args_in(char *arg, t_pb *p)
{
	if (!ft_strncmp("here_doc", arg, 8))
	{
		p->here_doc = 1;
		return (6);
	}
	else
	{
		p->here_doc = 0;
		return (5);
	}
}

void	here_doc(char **av, t_pb *p)
{
	int		tmpfile;
	char	*str;

	tmpfile = open(TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmpfile < 0)
		err_msg(ERR_HEREDOC);
	while (1)
	{
		write(1, "heredoc>", 8);
		str = get_next_line(0);
		str[ft_strlen(str) - 1] = '\0';
		if (!ft_strcmp(str, av[2]))
			break ;
		write(tmpfile, str, ft_strlen(str));
		write(tmpfile, "\n", 1);
		free(str);
	}
	p->fd_in = open(TMP_FILE, O_RDONLY);
	if (p->fd_in < 0)
	{
		unlink(TMP_FILE);
		err_msg(ERR_HEREDOC);
	}
}
