#include "../exec.h"

int	ft_env(char **argv, t_env *env)
{
	if (argv[1])
	{
		write (2, "bash: env: too many arguments\n", 31);
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
