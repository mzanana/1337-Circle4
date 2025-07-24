/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:31:35 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/24 12:30:59 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"
#include "../execution/exec.h"
int	g_exit_status = 0;

char *_ft_getenv(char *name_of_variable, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->key, name_of_variable) == 0)
            return (env->value);
        else
            env = env->next;
    }
    return (NULL);
}
t_env *_create_env(char **envp)
{
    t_env *env = NULL;
    int i = 0;
    int j;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] && envp[i][j] != '=')
            j++;
        if (envp[i][j] == '=')
        {
            t_env *new = malloc(sizeof(t_env));
            if (!new)
                return (NULL);
            
            new->key = ft_substr(envp[i], 0, j);
            new->value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
            new->next = NULL;
            if (!env)
                env = new;
            else
            {
                t_env *tmp = env;
                while (tmp->next)
                    tmp = tmp->next;
                tmp->next = new;
            }
        }
        i++;
    }
    return (env);
}

void	sigint_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	//free t_env
}

void print_ast(t_cmd *ast);

/*int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;

	t_env	*env;
	t_lexer	lexer;
	char	*input;
	t_cmd	*head;

	head = NULL;
	env = _create_env(envp);
	signal(SIGINT, sigint_prompt); // ctr + C
	while (1)
	{
		input = readline("JUST_TYPE# ");
		if (!input)
		{
			write(1, "exit\n", 5);
			free(input);
			//free t_env
			break ;
		}
		add_history(input);
		if (!find_error(lexer, input))
		{
			lexer = lexer_new(input);
			head = build_cmd_list(&lexer, env);
			if (head)
				f_main(head, envp, &env); 

				print_ast(head);

		}
		free(input);
	}
}*/
