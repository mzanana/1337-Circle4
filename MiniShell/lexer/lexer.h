/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:34:33 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/24 12:20:30 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../Libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "stdlib.h"
# include "string.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <unistd.h>

extern int			g_exit_status;

typedef struct s_lexer
{
	char			*input;
	char			c;
	size_t pos;      // index of c
	size_t len;      // length of input
	size_t read_pos; // next char index
}					t_lexer;

typedef enum s_token_type
{
	TOK_NULL = 0,
	TOK_PIPE,
	TOK_INPUT,
	TOK_OUTPUT,
	TOK_HERDOC,
	TOK_APPAND,
	TOK_WORD,
	TOK_DOUBLE,
	TOK_SINGLE,
	TOK_INVALID
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*literal;
	size_t			len;
	bool			space;
}					t_token;

// teconizing
t_token				lexer_next_token(t_lexer *lexer);
t_token				lexer_peek_next_token(t_lexer *lexer);
t_token				token_redir(t_lexer *lexer);
t_token				token_s_d_word(t_lexer *lexer);
t_token				token_word(t_lexer *lexer);

// token_help
t_token_type		toke_type(char c);
bool				skip_white_space(t_lexer *lexer);
int					ft_isspace(char c);
t_token				token_new(char *s, t_token_type type, size_t len);

// lexer_help

t_lexer				lexer_new(char *str);
void				read_char(t_lexer *lexer);

// error

int					check_errors(t_lexer *lexer, t_token curr);
int not_token(t_token n_tok);

int					check_first_tok(t_token *token);
int					find_error(t_lexer lexer, char *input);
void				print_error(char *pointer, size_t size);

// expand

int					is_var_char(int c);
int					is_start_char(int c);

#endif
