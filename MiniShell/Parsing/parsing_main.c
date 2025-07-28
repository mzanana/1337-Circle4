#include "parsing_hf.h"

const char      *token_type_to_str(t_token_type type)
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
char *ft_readline (const char *str)
{
	char *ret;

	ret = readline(str);
	if (!ret)
	{
		printf("exit\n");
		return NULL;
	}	
	if (*ret)
		add_history(ret);
	return (ret);
}

bool check_tokens(t_token *tokens, char **line)
{
	if (!tokens || !syntax_is_valid(tokens))
	{
		free(*line);
		*line = NULL;
		gc_calloc(-1);
		return 0;
	}
	return 1;
}

int	main()
{
	char	*line;
	t_token	*tokens;
	t_cmd	*commands;

	while (1)
	{
		line = ft_readline("minishell$ ");
		if (!line)
			break;
		tokens = tokenize_input(line);
		if (!check_tokens(tokens, &line))
			continue ;
		commands = tokens_to_commands(tokens);
		
		printf ("\nTokenizer output :\n");
		print_tokens(tokens);
		printf ("\nParser output :\n\n");
		gc_calloc(-1);
		free(line);
	}

	return (0);
}
