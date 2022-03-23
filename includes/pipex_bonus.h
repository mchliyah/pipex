/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:09:48 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/23 18:18:42 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_FORK "fork"
# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_PIPE "Pipe"
# define ERR_ENVP "Environment"
# define ERR_CMD "Command not found: "
# define ERR_HEREDOC "here_doc"
# define TMP_FILE "/Users/mchliyah/.TemporaryItems/.tmp_here_doc"

typedef struct s_pb
{
	int		fd_in;
	int		fd_out;
	char	*path;
	char	**c_pths;
	char	*cmd;
	char	**args;
	int		here_doc;
	int		pid;
	int		c_nbr;
	int		pipe_nb;
	int		*pipe;
	int		wt_nb;
	int		pidx;
}t_pb;

void	close_pipes(t_pb *p);

void	child(t_pb p, char **argv, char **envp);

void	free_prnt(t_pb *p);
void	child_free(t_pb *p);
void	pipe_free(t_pb *p);

char	*find_path(char **envp);
void	get_infile(char **argv, t_pb *p);
void	get_outfile(char *argv, t_pb *p);
char	*get_next_line(int fd);

int		args_in(char *arg, t_pb *p);
void	here_doc(char **argv, t_pb *p);

void	err_msg(char *err);
void	pipe_msg(char *arg);
int		write_msg(char *err);

char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_getstrdup(const char *src);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
