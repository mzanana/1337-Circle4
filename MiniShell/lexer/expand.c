/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:05:50 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/24 15:46:01 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"
#include "../execution/exec.h"

void	handle_env_var(char **res, char *var, size_t *i, t_env *env)
{
	size_t	j;
	char	*key;
	char	*val;
	char	*tmp;

	j = *i + 1;
	while (is_var_char(var[j]))
		j++;
	key = ft_substr(var, *i + 1, j - *i - 1);
	val = _ft_getenv(key, env);
	free(key);
	if (val)
	{
		tmp = ft_strjoin(*res, val);
		free(*res);
		*res = tmp;
	}
	*i = j;
}

char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*join_char(char c, char *res)
{
	char	t[2];
	char	*tmp;

	t[0] = c;
	t[1] = '\0';
	tmp = join_and_free(res, t);
	return (tmp);
}

char	*expand_variable(char *var, t_env *env)
{
	size_t	i;
	char	*res;
	char	*tmp;

	i = 0;
	res = ft_strdup("");
	while (var[i])
	{
		if (var[i] == '$' && var[i + 1] == '?')
		{
			tmp = ft_itoa(status_get());
			res = join_and_free_two(res, tmp);
			i += 2;
		}
		else if (var[i] == '$' && is_start_char(var[i + 1]))
			handle_env_var(&res, var, &i, env);
		else
		{
			res = join_char(var[i], res);
			i++;
		}
	}
	return (res);
}
