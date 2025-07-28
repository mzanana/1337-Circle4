#ifndef LEXER_H
#define LEXER_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>
# include "../../Libft/libft.h"

typedef	enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}	t_token_type;

typedef struct s_token
{
    char			*value;
    t_token_type	type;
	struct s_token	*next;
}	t_token;

char    *ft_strndup(char *str, size_t n);
int	is_operator(char c);
int	is_space(char c);
t_token	*token_new(char *value, t_token_type type);
void	token_add_back(t_token **head, t_token *new);
void	free_tokens(t_token **tokens);
bool    syntax_is_valid(t_token *tokens);
bool    check_pipe_syntax(t_token *token);
bool    check_redirection_syntax(t_token *tokens);
t_token	*tokenize_input(char *input);
bool	collect_word_token(t_token **tokens, char *input, int *i);
bool	append_quoted_segment(char **buffer, char *input, int *i);
char	*append_char_to_buffer(char *buffer, char c);
bool	handle_operator_token(t_token **tokens, char *input, int *i);
void    *gc_calloc(int size);
#endif
