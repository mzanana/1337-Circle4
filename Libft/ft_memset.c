/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 02:29:29 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 02:29:31 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			tmp;
	char			*str;
	char			num;

	str = (char *)s;
	num = (char)c;
	tmp = 0;
	while (tmp < n)
		str[tmp++] = num;
	return (s);
}
