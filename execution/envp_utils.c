/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:21:38 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 00:21:39 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_envp_array(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		free(envp[i++]);
	free(envp);
}

char	*join_key_value(char *key, char *value)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(key, "=");
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

char	**env_to_envp(t_env *env)
{
	char	**envp;
	t_env	*tmp;

	int (len), (i);
	len = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			len++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
			envp[i++] = join_key_value(tmp->key, tmp->value);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
