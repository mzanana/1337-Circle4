/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 08:05:27 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/15 11:53:11 by mzanana          ###   ########.fr       */
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
