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

/*
int	ft_env(char **argv, char **envp)
{
	int	i;

	if (argv[1])
	{
		write (2, "bash: env: too many arguments\n", 31);
		return (1);
	}
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	char	**args = ft_split("env", ' ');
	int	status = ft_env(av, envp);
	if (status == 1)
		printf("subject says : env with no options or arguments hhhhhh");

	for (int i = 0; args[i]; i++)
		free(args[i]);
	free(args);
}*/

/*int	main(int ac, char **av, char **envp)
{
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}*/
