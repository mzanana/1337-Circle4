/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:08:17 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/15 11:52:01 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dt;
	const char	*sc;

	dt = (char *)dest;
	sc = (const char *)src;
	if ((!dt && !sc) || dt == sc)
		return (dest);
	if (dt > sc)
	{
		while (n--)
			dt[n] = sc[n];
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}
