/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:05:26 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/16 22:46:28 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_p
{
	int		fd[2];
	int		pid1;
	int		pid2;
	int		fd_in;
	int		fd_out;
	char	**paths;
	char	**args;
	char	*cmd;
}	t_p;

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
t_p		*cmd_1(t_p *pip, char **av, char **envp);
t_p		*cmd_2(t_p *pip, char **av, char **envp);

#endif
