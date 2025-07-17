#include "../exec.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	env_add_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	print_export_list(t_env *env)
{
	while(env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

t_env	*find_new(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	update_or_add_env(char *arg, t_env **env)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*do_exist;
	size_t	key_len;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
	{
		write(2, "bash: export: invalid argument\n", 32);
		return (1);
	}
	key_len = equal_sign - arg;
	key = ft_substr(arg, 0, key_len);
	if (!key)
		return (1);
	value = ft_strdup(equal_sign + 1);
	if (!value)
	{
		free(key);
		return (1);
	}
	do_exist = find_new(*env, key);
	if (do_exist)
	{
		free(do_exist->value);
		free(key);
		do_exist->value = value;
	}
	else
		env_add_back(env, env_new(key, value));
	return (0);
}

int	ft_export(char **argv, t_env **env)
{
	int	i;

	if (!argv[1])
	{
		print_export_list(*env);
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		if (update_or_add_env(argv[i], env))
			return (1);
		i++;
	}
	return (0);
}
/*
int	main(int ac, char **av, char **envp)
{
	(void)ac;
	int	status;

	t_env	*env = init_env_test_vim(envp);
	status = ft_export(av, &env);
	if (status == 0)
	{
		while (env)
		{
			printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
}*/
