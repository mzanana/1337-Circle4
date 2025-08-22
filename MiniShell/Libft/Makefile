CC = gcc

RM  = rm -f

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC =   ft_isalpha.c ft_isdigit.c ft_isalnum.c \
        ft_strlen.c ft_memset.c ft_bzero.c \ ft_strchr.c \
        ft_atoi.c ft_strdup.c ft_substr.c \
        ft_strjoin.c ft_split.c ft_itoa.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar rcs $@ $^

clean :
	$(RM) *.o

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : clean fclean re
