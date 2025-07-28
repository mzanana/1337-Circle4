#include "../parsing_hf.h"

void	print_unexpected_token(const char *token)
{
	size_t	token_len;

	token_len = ft_strlen(token);
	write(2, "bash: syntax error near unexpected token `", 42);
	write(2, token, token_len);
	write(2, "'\n", 2);
}

void	print_unexpected_newline(void)
{
	write(2, "bash: syntax error near unexpected token `newline`\n", 52);
}

bool	is_redirection(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT || type == T_APPEND || type == T_HEREDOC);
}

bool	check_pipe_syntax(t_token *tokens)
{
	t_token	*curr;
	t_token	*next;

	curr = tokens;
	if (curr->type == T_PIPE) // pipe at the begening ==> | ls 
	{
		print_unexpected_token(curr->value); // `|'
		return (false);
	}
	while (tokens && tokens->next)
	{
		curr = tokens;
		next = tokens->next;
		if (curr->type == T_PIPE && next->type == T_PIPE) // two pipe ==> cat file || ls
		{
			print_unexpected_token(next->value);
			return (false);
		}
		tokens = tokens->next;
	}
	curr = tokens;
	if (curr->type == T_PIPE) // pipe at the end ==> ls -la | grep hello |
	{
		print_unexpected_newline();
		return (false);
	}
	return (true);
}

bool	check_redirection_syntax(t_token *tokens)
{
	t_token	*curr;
	t_token	*next;

	while (tokens && tokens->next)
	{
		curr = tokens;
		next = tokens->next;
		if (is_redirection(curr->type) && next->type != T_WORD) // redir not followed by a word
		{
			print_unexpected_token(next->value);
			return (false); // examples : (echo > <<)  (echo > |)
		}
		tokens = tokens->next;
	}
	if (tokens)
	{
		curr = tokens;
		if (is_redirection(curr->type)) // redir at the end ==> (echo >>)
		{
			print_unexpected_newline();
			return (false);
		}
	}
	return (true);
}

bool	syntax_is_valid(t_token *tokens)
{
	if (!tokens) // no tokens = valide
		return (true);
	if (!check_redirection_syntax(tokens))
		return (false);
	if (!check_pipe_syntax(tokens))
		return (false);
	return (true);
}