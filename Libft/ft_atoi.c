/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 02:28:51 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 02:28:54 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	space_check(const char *s, int *index)
{
	while ((s[*index]) && (((s[*index] >= 9) && (s[*index] <= 13
					|| s[*index] == 32))))
		*index += 1;
}

static void	sign_check(const char c, int *index, int *sign)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*sign = -1;
		*index += 1;
	}
}

int	ft_atoi(const char *str)
{
	int		sign;
	size_t	res;
	int		index;

	index = 0;
	space_check(str, &index);
	sign = 1;
	sign_check(str[index], &index, &sign);
	res = 0;
	while (str[index] && (str[index] >= 48 && str[index] <= 57))
	{
		if (res > LLONG_MAX)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		res = res * 10 + (str[index] - 48);
		index++;
	}
	return (res * sign);
}
