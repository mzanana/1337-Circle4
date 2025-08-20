#include "execution/exec.h"
#include "Parsing/parsing_hf.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char 	*input;
	t_token *tokens;
	t_cmd	*head;
	t_env	*env;

	env = init_env_list(envp);
	while (1)
	{
		setup_promt_signals();
		g_herdoc_stop = false;
		input = ft_readline("minishell$ ");
		if (!input)
			break;
		tokens = tokenize_input(input);
		if (!check_tokens(tokens, &input))
		{
			free(input);// double free maybe !!!!!!!!
			gc_calloc(-1);
			continue;
		}
		head = tokens_to_commands(tokens, env);
		if (!head)
		{
			free(input);
			status_set(1);
			gc_calloc(-1);
			continue;
		}
		if (!process_all_heredocs(head, env))
		{
			free(input);
			status_set(130);
			continue;
		}
		if (head)
		{
			status_set(run_command(head, &env));
			cleanup_heredocs(head);
		}
		gc_calloc(-1);
		free(input);
	}
	free_env_list(env);
	return (status_get());
}
