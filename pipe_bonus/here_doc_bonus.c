/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:08:41 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/19 23:44:04 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	args_in(char *arg, t_pb *p)
{
	if (!ft_strncmp("here_doc", arg, 9))
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
