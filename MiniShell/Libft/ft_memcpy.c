/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 03:08:10 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/15 21:36:20 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		tmp;
	const char	*s;
	char		*d;

	if (!dest && !src)
		return (dest);
	if (dest == src)
		return (dest);
	d = (char *)dest;
	s = (const char *)src;
	tmp = 0;
	while (tmp < n)
	{
		d[tmp] = s[tmp];
		tmp++;
	}
	return (dest);
}
