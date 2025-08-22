/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:21:15 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 00:21:16 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	log_err(char *msg)
{
	write(2, msg, ft_strlen(msg));
}

int	ft_cd(char **argv)
{
	if (!argv[1])
	{
		log_err("minishell: cd : missing argument\n");
		return (1);
	}
	if (argv[2])
	{
		log_err("minishell: cd: too many arguments\n");
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
