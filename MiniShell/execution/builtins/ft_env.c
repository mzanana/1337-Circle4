#include "../exec.h"

int	ft_env(char **argv, t_env *env)
{
	if (argv[1])
	{
		log_err("minishell: env: too many arguments\n");
		return (1);
	}
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
