/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 01:58:40 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 01:58:41 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parsing/parsing_hf.h"
#include "execution/exec.h"

static int	process_tokens(t_token *tokens, char *input, t_env *env)
{
	t_cmd	*head;

	head = tokens_to_commands(tokens, env);
	if (!head)
	{
		free(input);
		status_set(1);
		gc_calloc(-1);
		return (0);
	}
	if (!process_all_heredocs(head, env))
	{
		free(input);
		status_set(130);
		return (0);
	}
	status_set(run_command(head, &env));
	cleanup_heredocs(head);
	return (1);
}

static void	handle_input(char *input, t_env *env)
{
	t_token	*tokens;

	tokens = tokenize_input(input);
	if (!check_tokens(tokens, &input))
	{
		free(input);
		gc_calloc(-1);
		return ;
	}
	if (!process_tokens(tokens, input, env))
		return ;
	gc_calloc(-1);
	free(input);
}

static void	minishell_loop(t_env *env)
{
	char	*input;

	while (1)
	{
		setup_promt_signals();
		g_herdoc_stop = false;
		input = ft_readline("minishell$ ");
		if (!input)
			break ;
		handle_input(input, env);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	(void)av;
	env = init_env_list(envp);
	minishell_loop(env);
	free_env_list(env);
	return (status_get());
}
