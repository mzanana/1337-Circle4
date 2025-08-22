/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 02:29:23 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 02:29:24 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_count(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		count;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	count = num_count(n);
	ret = malloc(sizeof(char) * (count + 1));
	if (!ret)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		ret[0] = '-';
	}
	ret[count] = '\0';
	while (n)
	{
		ret[--count] = n % 10 + 48;
		n /= 10;
	}
	return (ret);
}
