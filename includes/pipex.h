/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <mchliyah@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:05:26 by mchliyah          #+#    #+#             */
/*   Updated: 2023/01/16 21:54:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
#include <sys/wait.h>

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_ENVP "Environment"
# define ERR_CMD "Command not found "

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

void	err_msg(char *err);
void	pipe_msg(char *arg);
int		write_msg(char *err);

#endif
