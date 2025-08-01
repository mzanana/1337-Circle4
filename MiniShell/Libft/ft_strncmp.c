/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:42:33 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/17 09:59:09 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		ret;
	size_t	index;

	if (n == 0 || (!s1 && !s2))
		return (0);
	index = 0;
	while (s1[index] && s2[index] && ((unsigned char)*(s1
				+ index) == (unsigned char)*(s2 + index)) && index < (n - 1))
		index++;
	ret = ((unsigned char)*(s1 + index)) - ((unsigned char)*(s2 + index));
	return (ret);
}
