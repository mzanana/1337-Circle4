#ifndef PARSING_HF_H
#define PARSING_HF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stddef.h>
# include <unistd.h>
# include "../Libft/libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/ioctl.h> 

// Lexer struct : 
//
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
	bool			is_quoted;
	struct s_token	*next;
}	t_token;


// Parser Struct :

typedef struct s_redir
{
	t_token_type		type;
	char		*filename;
	bool		quoted;
	bool	is_temp;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char		**argv;
	t_redir		*redir;
	struct s_cmd	*next;
} t_cmd;

// Environement Struct :

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;


// Functions Prototypes :
char *ft_readline (const char *str);
char    *ft_strndup(char *str, size_t n);
int	is_operator(char c);
int	is_space(char c);
t_token	*token_new(char *value, t_token_type type, bool quoted);
void	token_add_back(t_token **head, t_token *new);
bool    syntax_is_valid(t_token *tokens);
bool    check_pipe_syntax(t_token *token);
bool    check_redirection_syntax(t_token *tokens);
t_token	*tokenize_input(char *input);
bool	collect_word_token(t_token **tokens, char *input, int *i);
bool	append_quoted_segment(char **buffer, char *input, int *i);
char	*append_char_to_buffer(char *buffer, char c);
bool	handle_operator_token(t_token **tokens, char *input, int *i);
void    *gc_calloc(int size);

void print_parsed_commands(t_cmd *cmds);
t_cmd *tokens_to_commands(t_token *tokens);
void ft_expand (t_cmd *command, t_env *env);
bool check_tokens(t_token *tokens, char **line);
void	expand_into(char *dst, char *src, t_env *env);
bool    process_all_heredocs(t_cmd *cmds, t_env *env);
void    cleanup_heredocs(t_cmd *cmd);
int	new_len(char *s, t_env *env);
int	ft_strcmp(char *s1, char *s2);



void	status_set_tmp(int value);
int	status_get_tmp(void);
#endif
