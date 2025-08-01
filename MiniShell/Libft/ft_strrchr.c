/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:22:32 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/15 11:44:28 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len > 0)
		if (s[len--] == (char)(c))
			return ((char *)(s + len + 1));
	if (s[len] == (char)c)
		return ((char *)(s + len));
	return (0);
}
