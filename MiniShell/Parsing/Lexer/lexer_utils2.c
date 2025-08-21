#include "../parsing_hf.h"

bool	handle_word_token_segment(char **buffer, char *input, \
	int *i, bool *quoted)
{
	if (input[*i] == '\'' || input[*i] == '"')
	{
		if (!append_quoted_segment(buffer, input, i))
			return (false);
		*quoted = 1;
	}
	else
	{
		*buffer = append_char_to_buffer(*buffer, input[*i]);
		if (!(*buffer))
			return (false);
		(*i)++;
	}
	return (true);
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
		if (!handle_word_token_segment(&buffer, input, i, &quoted))
			return (false);
	}
	new_token = token_new(buffer, T_WORD, quoted);
	if (!new_token)
		return (false);
	token_add_back(tokens, new_token);
	return (true);
}

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
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
				return (NULL);
		}
		else
		{
			if (!collect_word_token(&tokens, input, &i))
				return (NULL);
		}
	}
	return (tokens);
}
