#include"lexer.h"
bool	handle_quoted_token(t_token **tokens, char *input, int *i)
{
	char quote_char;
	int start;
	int len;
	char *value;
	t_token *new_token;

	quote_char = input[*i];
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (input[*i] != quote_char)
	{
		write(2, "bash: unexpected EOF while looking for matching `", 49);
		write(2, &quote_char, 1);
		write(2, "`\n", 2);
		return (false);
	}
	len = (*i) - start;
	value = ft_strndup(input + start, len);
	if (!value)
		return (false);
	new_token = token_new(value, T_WORD, true, quote_char == '\'');
	if (!new_token)
	{
		free(value);
		return (false);
	}
	token_add_back(tokens, new_token);
	(*i)++;
	return (true);
}

bool	handle_word_token(t_token **tokens, char *input, int *i)
{
	int	start;
	char	*value;
	t_token	*new_token;

	start = *i;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]) && input[*i] != '\'' && input[*i] != '"')
		(*i)++;
	value = ft_strndup(input + start, *i - start);
	if (!value)
		return (false);
	new_token = token_new(value, T_WORD, false, false);
	if (!new_token)
	{
		free(value);
		return (false);
	}
	token_add_back(tokens, new_token);
	return (true);
}

bool	handle_operator_token(t_token **tokens, char *input, int *i)
{
	char	*value;
	t_token_type	type;
	t_token	*new_token;

	if (input[*i] == '|')
	{
		type = T_PIPE;
		value = ft_strndup("|", 1);
		(*i)++;
	}
	else if (input[*i] == '<' && input[*i + 1] == '<')
	{
		type = T_HEREDOC;
		value = ft_strndup("<<", 2);
		(*i) += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		type = T_APPEND;
		value = ft_strndup(">>", 2);
		(*i) += 2;
	}
	else if (input[*i] == '<')
	{
		type = T_REDIR_IN;
		value = ft_strndup("<", 1);
		(*i)++;
	}
	else (input[*i] == '>')
	{
		type = T_REDIR_OUT;
		value = ft_strndup(">", 1);
		(*i)++;
	}
	if (!value)
		return (false);
	new_token = token_new(value, type, false, false);
	if (!new_token)
	{
		free(value);
		return (false);
	}
	token_add_back(tokens, new_token);
	return (true);
}


t_token	*tokenize_input(char *input)
{
	t_token *tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '"' || input[i] == '\'')
		{
			if (!handle_quoted_token(&tokens, input, &i))
			{
				free_tokens(&tokens);
				return (NULL);
			}
		}
		else if (is_operator(input[i]))
		{
			if (!handle_operator_token(&tokens, input, &i))
			{
				free_tokens(&tokens);
				write(2, "lexer error: invalid operator\n", 31);
				return (NULL);
			}
		}
		else
		{
			if (!handle_word_token(&tokens, input, &i))
			{
				free_tokens(&tokens);
				write (2, "lexer error: failed to allocate word\n", 37);
				return (NULL);
			}
		}
		i++;
	}
	return (tokens);
}
int main()
{
	char *line;
	t_token *tokens;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		tokens = tokenize_input(line);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		if (!syntax_is_valid(tokens))
		{
			free_tokens(&tokens);
			free(line);
			continue ;
		}
		free_tokens(&tokens);
		free(line);
	}
	return (0);
}
