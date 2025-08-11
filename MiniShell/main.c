#include "execution/exec.h"
#include "Parsing/parsing_hf.h"


int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	int 	last_status;
	char 	*input;
	t_token *tokens;
	t_cmd	*head;
	t_env	*env;

	env = init_env_list(envp);
	while (1)
	{
		input = ft_readline("minishell$ ");
		if (!input)
			break;
		tokens = tokenize_input(input);
		if (!check_tokens(tokens, &input))
			continue;
		head = tokens_to_commands(tokens);
		ft_expand(head, env);
		if (head)
		{
			last_status = run_command(head, &env);
			free_cmds(head);
			status_set(last_status);
		}
		free(input);
	}
	return (last_status);
}

