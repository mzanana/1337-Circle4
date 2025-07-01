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
	}
	return (0);
}