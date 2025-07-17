#include "../exec.h"

t_env	*init_env_list(char **envp)
{
	t_env	*env = NULL;
	t_env	*new;
	char	*equal_sign;
	char	*key;
	char	*value;

	while(*envp)
	{
		equal_sign = ft_strchr(*envp, '=');
		if (!equal_sign)
		{
			envp++;
			continue ;
		}
		key = ft_substr(*envp, 0, equal_sign - *envp);
		value = ft_strdup(equal_sign + 1);
		new = env_new(key, value);
		env_add_back(&env, new);
		envp++;
	}
	return (env);
}


/*int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*env;

	env = init_env_list(envp);
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}*/
