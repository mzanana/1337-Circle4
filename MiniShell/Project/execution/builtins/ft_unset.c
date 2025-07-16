#include "../exec.h"

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->key);
		free(node->value);
		free(node);
	}
}

void	remove_env_var(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free_env_node(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
int	ft_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		remove_env_var(env, argv[i]);
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;

	t_env	*env = init_env_list(envp);
	ft_unset(av, &env);
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
