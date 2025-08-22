/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:21:13 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 00:21:14 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	print_export_error(char *arg)
{
	log_err("minishell: export: `");
	log_err(arg);
	log_err("': not a valid identifier\n");
}

int	_is_var_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

void	print_export_list(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}
