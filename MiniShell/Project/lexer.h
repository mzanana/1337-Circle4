#ifndef HEADER_H
#define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

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
	bool			was_quoted;
	bool			was_single_quoted;
	struct s_token	*next;
}	t_token;

#endif