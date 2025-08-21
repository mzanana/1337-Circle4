/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:21:19 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 00:21:20 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

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

void	apply_env(char *key, char *value, t_env **env, char *eq)
{
	t_env	*do_exist;

	do_exist = find_new(*env, key);
	if (do_exist)
	{
		free(key);
		if (eq)
		{
			free(do_exist->value);
			do_exist->value = value;
		}
	}
	else
		env_add_back(env, env_new(key, value));
}

int	update_or_add_env(char *arg, t_env **env)
{
	char	*equal_sign;
	char	*key;
	char	*value;
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
	apply_env(key, value, env, equal_sign);
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
