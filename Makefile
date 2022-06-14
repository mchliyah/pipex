# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/21 18:13:54 by mchliyah          #+#    #+#              #
#    Updated: 2022/06/14 20:03:49 by mchliyah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = pipex_bonus
CC = gcc
FLAGS = -Werror -Wextra -Wall

RM = rm -f

FILES = \
		./mandatory/pipex.c \
		./mandatory/ft_split.c\
		./mandatory/ft_strncmp.c\
		./mandatory/ft_strjoin.c \
		./mandatory/ft_strlen.c	\
		./mandatory/cmds.c	\
		./mandatory/error.c

OBJECTS = $(FILES:.c=.o)

FILES_bonus =	\
				./pipe_bonus/pipex_bonus.c\
				./pipe_bonus/free_bonus.c\
				./pipe_bonus/cmds_bonus.c\
				./pipe_bonus/files_bonus.c\
				./mandatory/ft_split.c\
				./mandatory/ft_strncmp.c\
				./mandatory/ft_strjoin.c\
				./mandatory/ft_strlen.c	\
				./pipe_bonus/error_bonus.c	\
				./pipe_bonus/here_doc_bonus.c \
				./pipe_bonus/get_next_line_utils.c\
				./pipe_bonus/get_next_line.c	\
				./pipe_bonus/strcmp.c

OBJECTS_bonus = $(FILES_bonus:.c=.o)

%.o: %.c
	@gcc $(FLAGS) -c $^ -o $@

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m

.PHONY : all clean fclean rebonus

all : $(NAME)

$(NAME) :  $(OBJECTS)
	@$(CC) $(FILES) -o $(NAME)
	@echo "$(C_GREEN)[PIPEX MANDATORY CREATED!]$(C_RES)"

bonus : $(BONUS)

$(BONUS) : $(OBJECTS_bonus)
	@$(CC) $(FILES_bonus) -o $(BONUS)
	@echo "$(C_L_BLUE)[PIPEX BONUS CREATED!]$(C_RES)"

clean : 
	@$(RM) $(OBJECTS) $(OBJECTS_bonus)
	@echo "$(C_RED)[PIPEX OBJECTS DELETED!]$(C_RES)"

fclean : clean
	@$(RM) $(NAME) $(BONUS)
	@echo "$(C_RED)[PIPEX OBJECTS && EXECUTABLES DELETED!]$(C_RES)"

re : fclean all

rebonus : fclean bonus