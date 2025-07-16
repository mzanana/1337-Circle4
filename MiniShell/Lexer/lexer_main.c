#include "lexer.h"

bool	handle_operator_token(t_token **tokens, char *input, int *i)
{
	char	*value;
	t_token_type	type;
	t_token	*new_token;

	value = NULL;
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
	else if (input[*i] == '>')
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

char	*append_char_to_buffer(char *buffer, char c)
{
	char	*new_buf;
	size_t	len;
	size_t	i;

	if (!buffer)
		len = 0;
	else
		len = ft_strlen(buffer);
	new_buf = malloc(len + 2);
	if (!new_buf)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_buf[i] = buffer[i];
		i++;
	}
	new_buf[i++] = c;
	new_buf[i] = '\0';
	free(buffer);
	return (new_buf);
}

bool	append_quoted_segment(char **buffer, char *input, int *i)
{
	char	quote = input[*i];
	*buffer = append_char_to_buffer(*buffer, quote);
	(*i)++;
	while (input[*i])
	{
		*buffer = append_char_to_buffer(*buffer, input[*i]);
		if (!(*buffer))
			return (false);
		if (input[*i] == quote)
		{
			(*i)++;
			return (true);
		}
		(*i)++;
	}
	write(2, "bash: unexpected EOF while looking for matching `", 49);
	write(2, &quote, 1);
	write(2, "'\n", 2);
	return (false);
}

bool	collect_word_token(t_token **tokens, char *input, int *i)
{
	char	*buffer;
	t_token	*new_token;

	buffer = NULL;
	while (input[*i])
	{
		if (is_space(input[*i]) || is_operator(input[*i]))
			break ;
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!append_quoted_segment(&buffer, input, i))
			{
				free(buffer);
				return (false);
			}
		}
		else
		{
			buffer = append_char_to_buffer(buffer, input[*i]);
			if (!buffer)
				return (false);
			(*i)++;
		}
	}
	new_token = token_new(buffer, T_WORD, false, false);
	if (!new_token)
	{
		free(buffer);
		return (false);
	}
	token_add_back(tokens, new_token);
	return (true);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens = NULL;
	int		i;

	i = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_operator(input[i]))
		{
			if (!handle_operator_token(&tokens, input, &i))
			{
				free_tokens(&tokens);
				//write(2, "lexer error: invalid operator\n", 31);
				return (NULL);
			}
		}
		else
		{
			if (!collect_word_token(&tokens, input, &i))
			{
				free_tokens(&tokens);
				//write(2, "lexer error: failed to collect word\n", 37);
				return (NULL);
			}
		}
	}
	return (tokens);
}


const char	*token_type_to_str(t_token_type type)
{
	if (type == T_WORD)
		return ("T_WORD");
	else if (type == T_PIPE)
		return ("T_PIPE");
	else if (type == T_REDIR_IN)
		return ("T_REDIR_IN");
	else if (type == T_REDIR_OUT)
		return ("T_REDIR_OUT");
	else if (type == T_APPEND)
		return ("T_APPEND");
	else
		return ("T_HEREDOC");
}

void	print_tokens(t_token *tokens)
{
	int		i = 0;

	while (tokens)
	{
		printf("Token[%d]: %-13s | Type: %-13s \n",
			i++,
			tokens->value,
			token_type_to_str(tokens->type));
		tokens = tokens->next;
	}
}

int	main()
{
	char	*line;
	t_token	*tokens;

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
		print_tokens(tokens);
		free_tokens(&tokens);
		free(line);
	}
	return (0);
}
