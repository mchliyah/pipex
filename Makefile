NAME = pipex

CC = gcc
#CFLAGS = -Werror -Wextra -Wall

RM = rm -f

FILES = pipex.c \
		ft_split.c\
		ft_strncmp.c

OBJECTS = $(subst .c,.o,$(FILES))

all : $(NAME)

$(NAME) :  $(OBJECTS)
	$(CC) $(CFLAG) $(FILES) -fsanitize=address -g -o $(NAME)

clean : 
	$(RM) $(OBJECTS) $(BONUOBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all