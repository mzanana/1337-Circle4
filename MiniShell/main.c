#include "execution/exec.h"
#include "Parsing/parsing_hf.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	int 	last_status= 0;
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
			free(input);
			gc_calloc(-1);
			continue;
		}
		head = tokens_to_commands(tokens);
		
		if (!process_all_heredocs(head, env))
		{
			free(input);
			status_set(130);
			continue ;
		}
		ft_expand(head, env);
		if (head)
		{
			last_status = run_command(head, &env);
			cleanup_heredocs(head);
			status_set(last_status);
		}
		gc_calloc(-1);
		free(input);
	}
	free_env_list(env);
	return (last_status);
}
