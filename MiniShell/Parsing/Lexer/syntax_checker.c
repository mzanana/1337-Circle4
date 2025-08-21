#include "../parsing_hf.h"

bool	is_pipe_error(t_token *curr, t_token *next)
{
	if (curr->type == T_PIPE && (!next || next->type == T_PIPE))
	{
		if (!next)
			print_unexpected_newline();
		else
			print_unexpected_token(next->value);
		return (true);
	}
	return (false);
}

bool	check_pipe_syntax(t_token *tokens)
{
	t_token	*curr;
	t_token	*next;

	curr = tokens;
	if (curr->type == T_PIPE)
	{
		print_unexpected_token(curr->value);
		return (false);
	}
	while (tokens && tokens->next)
	{
		curr = tokens;
		next = tokens->next;
		if (is_pipe_error(curr, next))
			return (false);
		tokens = tokens->next;
	}
	if (tokens && tokens->type == T_PIPE)
	{
		print_unexpected_newline();
		return (false);
	}
	return (true);
}

bool	is_redirection_error(t_token *curr, t_token *next)
{
	if (is_redirection(curr->type) && (!next || next->type != T_WORD))
	{
		if (!next)
			print_unexpected_newline();
		else
			print_unexpected_token(next->value);
		return (true);
	}
	return (false);
}

bool	check_redirection_syntax(t_token *tokens)
{
	t_token	*curr;
	t_token	*next;

	while (tokens && tokens->next)
	{
		curr = tokens;
		next = tokens->next;
		if (is_redirection_error(curr, next))
			return (false);
		tokens = tokens->next;
	}
	if (tokens && is_redirection(tokens->type))
	{
		print_unexpected_newline();
		return (false);
	}
	return (true);
}

bool	syntax_is_valid(t_token *tokens)
{
	if (!tokens)
		return (true);
	if (!check_redirection_syntax(tokens))
		return (false);
	if (!check_pipe_syntax(tokens))
		return (false);
	return (true);
}
