#include "../exec.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s1[i] == s2[i])
// 		i++;
// 	return (s1[i] - s2[i]);
// }

int	_is_var_char(int c)
{
	return (ft_isalnum(c) || c == '_');
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

void	print_export_error(char *arg)
{
	write(2, "bash: export: `", 15);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
}

int	check_valide_key(char *arg)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(arg[0]) || arg[0] == '_' ))
	{
		print_export_error(arg);
		return (1);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (!_is_var_char(arg[i]))
		{
			print_export_error(arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int	update_or_add_env(char *arg, t_env **env)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	t_env	*do_exist;
	size_t	key_len;

	value = NULL;
	equal_sign = ft_strchr(arg, '=');
	if (check_valide_key(arg))
		return (1);
	if (equal_sign)
	{
		key_len = equal_sign - arg;
		key = ft_substr(arg, 0, key_len);
		value = ft_strdup(equal_sign + 1);
	}
	else
		key = ft_strdup(arg);
	if (!key || (equal_sign && !value))
	{
		free(key);
		free(value);
		return (1);
	}
	do_exist = find_new(*env, key);
	if (do_exist)
	{
		free(key);
		if (equal_sign)
		{
			free(do_exist->value);
			do_exist->value = value;
		}
	}
	else
		env_add_back(env, env_new(key, value));
	return (0);
}

// i still need to print the env in the right order !!!!!
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
