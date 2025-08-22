/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_length.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:20:23 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 03:13:24 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution/exec.h"

char	*env_val(char *key, t_env *env)
{
	t_env	*e;

	e = env;
	while (e)
	{
		if (e->key && !ft_strcmp(e->key, key))
			return (e->value);
		e = e->next;
	}
	return (NULL);
}

int	get_var_size(char *str, int i, int j, t_env *env)
{
	char	*val;
	char	*key;

	key = ft_substr2(str, i, j - i);
	val = env_val(key, env);
	if (!val)
		return (0);
	return (ft_strlen(val));
}

int	env_len(char *str, int *i, t_env *env)
{
	int	ret;
	int	j;

	ret = 1;
	j = *i + 1;
	while (str[j] && var_middle(str[j]))
	{
		ret++;
		j++;
	}
	ret = get_var_size(str, *i + 1, j, env) - ret;
	(*i) = j - 1;
	return (ret);
}

int	new_len(char *s, int heredoc, t_env *env)
{
	int (i), (len), (sq), (dq);
	i = 0;
	len = ft_strlen(s) + 1;
	sq = 0;
	dq = 0;
	while (s[i])
	{
		if (!heredoc && (s[i] == '\'' || s[i] == '"'))
			quote_checker(s[i], &sq, &dq, 0);
		else if (s[i] == '$' && !sq && s[i + 1] && \
			(var_start(s[i + 1]) || s[i + 1] == '?'))
		{
			if (s[i + 1] == '?')
				len += 3;
			else
				len += env_len(s, &i, env);
		}
		i++;
	}
	return (len);
}
