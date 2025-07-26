#include "./Lexer/lexer.h"

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
			gc_calloc(-1);
			continue ;
		}
		if (!syntax_is_valid(tokens))
		{
			free(line);
			gc_calloc(-1);
			continue ;
		}
		printf ("\nTokenizer output :\n");
		print_tokens(tokens);
		printf ("\nParser output :\n\n");
		gc_calloc(-1);
		free(line);
	}

	return (0);
}
