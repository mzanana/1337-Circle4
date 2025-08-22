/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_hf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 02:00:42 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 03:45:26 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_HF_H
# define PARSING_HF_H

# include "../Libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern bool			g_herdoc_stop;
// Lexer struct :
typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC
}					t_token_type;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}					t_gc;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	bool			is_quoted;
	struct s_token	*next;
}					t_token;

// Parser Struct :

typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	bool			quoted;
	bool			is_temp;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	bool			expansion;
	t_redir			*redir;
	struct s_cmd	*next;
}					t_cmd;

// Environement Struct :

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;
typedef struct s_exp_vars
{
	int				i;
	int				j;
	int				sq;
	int				dq;
	int				k;
	int				e;
	int				f;
	char			*key;
	char			*map;
	char			*nmap;
}					t_exp_vars;

// Functions Prototypes :
int					env_len(char *str, int *i, t_env *env);
char				*ft_readline(const char *str);
char				*ft_strndup(char *str, size_t n);
int					is_operator(char c);
int					is_space(char c);
t_token				*token_new(char *value, t_token_type type, bool quoted);
void				token_add_back(t_token **head, t_token *new);
bool				syntax_is_valid(t_token *tokens);
bool				check_pipe_syntax(t_token *token);
bool				check_redirection_syntax(t_token *tokens);
t_token				*tokenize_input(char *input);
bool				collect_word_token(t_token **tokens, char *input, int *i);
bool				append_quoted_segment(char **buffer, char *input, int *i);
char				*append_char_to_buffer(char *buffer, char c);
bool				handle_operator_token(t_token **tokens, char *input,
						int *i);
void				*gc_calloc(int size);
bool				is_redirection(t_token_type type);
void				print_unexpected_token(const char *token);
void				print_unexpected_newline(void);
bool				is_pipe_error(t_token *curr, t_token *next);
bool				is_redirection_error(t_token *curr, t_token *next);
void				print_parsed_commands(t_cmd *cmds);
t_cmd				*tokens_to_commands(t_token *tokens, t_env *env);
bool				check_tokens(t_token *tokens, char **line);

void				expand_into(char *dst, char *src, t_exp_vars *vars,
						t_env *env);
bool				process_all_heredocs(t_cmd *cmds, t_env *env);
void				cleanup_heredocs(t_cmd *cmd);
int					new_len(char *s, int heredoc, t_env *env);
int					ft_strcmp(char *s1, char *s2);

t_cmd				*handle_redirection(t_token **tokens, t_env *env,
						t_cmd *tmp);
t_redir				*redir_maker(t_token_type type, char *value,
						bool is_quoted);
void				cmd_redir_fill(t_redir **redir, t_token_type type,
						char *value, bool is_quoted);

void				status_set(int value);
int					status_get_tmp(void);

char				*env_val(char *key, t_env *env);
char				*env_val(char *key, t_env *env);
char				*env_val(char *key, t_env *env);
void				handle_exit_status(char *dst, t_exp_vars *vars);
void				handle_variable_expansion(char *dst, char *src,
						t_exp_vars *vars, t_env *env);
void				fill_nmap_and_dst(char *dst, char *src, t_exp_vars *vars);
char				*ft_substr2(char const *s, unsigned int start, size_t len);
int					var_start(char c);
int					var_middle(char c);
int					quote_checker(char c, int *sq, int *dq, int *cnt);
char				*expand_it(char *str, t_env *env);
char				*expand_heredoc(char *str, t_env *env);
char				*remove_qoutes_if_needed(char *s, char *nmap);

char				*ft_strdup2(char *s);
char				*ft_strjoin2(char const *s1, char const *s2);
bool				join_current_dir(t_cmd *cmd, char *patern);
bool				wildcmp(char *str, char *pattern);
bool				_wildcmp_help(char *str, char *pattern);
bool				ends_with_substr(char *str, char *end, size_t i);
char				*ft_strstr(char *str, char *little, size_t z);

char				*join_current_dir_redi(char *patern);
char				*get_single_file_or_null(char *patern);
int					asterisk_in_filename(char *target, t_cmd *cmd,
						t_token *tok);
void				cmd_argv_fill(t_cmd *cmd, char *value);
char				*ft_strjoin2(char const *s1, char const *s2);
void				write_val(char *dst, int *i, char *val);
void				reset_prompt_signals(void);
void				sigint_handler_herdoc(int signal);
char				*make_tempfile(void);
void				cleanup_heredocs(t_cmd *cmd);
int					open_tmpfile(char **tmp_path);

#endif
