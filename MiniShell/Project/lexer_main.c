#include"lexer.h"

t_token	*tokenize_input(char *input)
{
	t_token *tokens;

	return (tokens);
}

main()
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