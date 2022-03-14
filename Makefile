NAME = pipex
BONUS = pipex_bonus
CC = gcc
#CFLAGS = -Werror -Wextra -Wall

RM = rm -f

FILES = pipex.c \
		ft_split.c\
		ft_strncmp.c\
		ft_strjoin.c \
		ft_strlen.c	\
		cmds.c

FILES_bonus =	pipex_bonus.c\
				free_bonus.c\
				cmds_bonus.c\
				files_bonus.c\
				ft_split.c\
				ft_strncmp.c\
				ft_strjoin.c \
				ft_strlen.c	\
				error_bonus.c
OBJECTS = $(subst .c,.o,$(FILES))
OBJECTS_bonus = $(subst .c,.o,$(FILES_bonus))

all : $(NAME)

$(NAME) :  $(OBJECTS)
	$(CC) $(CFLAG) $(FILES) -o $(NAME)
bonus : $(OBJECTS_bonus)

$(OBJECTS_bonus) : $(FILES_bonus)
	$(CC) $(CFLAG) $(FILES_bonus) -o $(BONUS)

clean : 
	$(RM) $(OBJECTS) $(OBJECTS_bonus)
	$(RM) $(OBJECTS_bonus) $(OBJECTS_bonus)

fclean : clean
	$(RM) $(NAME)

re : fclean all