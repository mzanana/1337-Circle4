SCC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb3 -g3
LINKERS = -L ../libft -lft -lreadline 

SRC_FILES= $(wildcard *.c ast_print/*.c)
SRC_OBJ= $(SRC_FILES:%.c=%.o)
LIBFT_DIR= ../libft
libft_rule = ../libft/libft.a

NAME=minishell

all: $(NAME)

$(libft_rule):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(SRC_OBJ) $(libft_rule) 
	$(CC) $(SRC_OBJ) $(LINKERS) -o $(NAME)

clean: 
	$(RM) $(SRC_OBJ) $(OBJ_BONUS)
	$(MAKE) -s -C $(LIBFT_DIR) clean

fclean:
	$(RM) $(SRC_OBJ) $(NAME) 
	$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all libft_rule clean fclean re
.SECONDARY: $(SRC_OBJ)
