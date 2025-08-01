#include "../parsing_hf.h"

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
	new_token = token_new(value, type, 0);
	if (!new_token)
		return (false);
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
	new_buf = gc_calloc(len + 2);
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
	bool	quoted;

	buffer = NULL;
	quoted = 0;
	while (input[*i])
	{
		if (is_space(input[*i]) || is_operator(input[*i]))
			break ;
		if (input[*i] == '\'' || input[*i] == '"')
		{
			if (!append_quoted_segment(&buffer, input, i))
				return (false);
			quoted = 1;
		}
		else
		{
			buffer = append_char_to_buffer(buffer, input[*i]);
			if (!buffer)
				return (false);
			(*i)++;
		}
	}
	new_token = token_new(buffer, T_WORD, quoted);
	if (!new_token)
		return (false);
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
				write(2, "lexer error: invalid operator\n", 31);
				return (NULL);
			}
		}
		else
		{
			if (!collect_word_token(&tokens, input, &i))
			{
				write(2, "lexer error: failed to collect word\n", 37);
				return (NULL);
			}
		}
	}
	return (tokens);
}