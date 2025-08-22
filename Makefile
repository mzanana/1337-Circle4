CC = cc
CFLAGS = -Wall -Wextra -Werror 
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = execution/builtins/export_utils.c execution/builtins/ft_cd.c execution/builtins/ft_echo.c execution/builtins/ft_env.c execution/builtins/ft_exit.c \
		execution/builtins/ft_export.c execution/builtins/ft_pwd.c execution/builtins/ft_unset.c execution/builtins/init_env_list.c execution/envp_utils.c \
		execution/find_cmd_path.c execution/pipe_child.c execution/pipe_exec.c execution/pipe_utils.c execution/redirections.c execution/run_cmd.c \
		execution/signals.c execution/status.c execution/utils.c Parsing/Lexer/lexer_utils.c Parsing/Lexer/lexer_utils2.c Parsing/Lexer/lexer.c \
		Parsing/Lexer/syntax_checker_helper.c Parsing/Lexer/syntax_checker.c Parsing/Parser/expand_helper.c Parsing/Parser/expand_helper2.c \
		Parsing/Parser/expand_length.c Parsing/Parser/expand.c Parsing/Parser/heredoc_utils.c Parsing/Parser/heredoc_utils2.c Parsing/Parser/heredoc.c \
		Parsing/Parser/parser_helper.c Parsing/Parser/parser_helper2.c Parsing/Parser/parser.c Parsing/Parser/wildcard_helper.c Parsing/Parser/wildcard.c \
		Parsing/parsing_main.c G_collector.c main.c

OBJ = $(SRC:%.c=%.o)
NAME = minishell
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)


clean:
	@$(RM) $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

re: fclean all

.SECONDARY: $(OBJ)
.PHONY: all clean fclean re