/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 14:05:32 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/23 18:18:42 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	write_msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	pipe_msg(char *arg)
{
	write(2, arg, ft_strlen(arg));
	write(2, " : ", 3);
	write(2, ERR_CMD, ft_strlen(ERR_CMD));
	write(2, "\n", 1);
}

void	err_msg(char *err)
{
	perror(err);
	exit (1);
}
