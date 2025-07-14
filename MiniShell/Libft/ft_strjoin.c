/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 05:51:51 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/17 18:17:42 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	index;
	size_t	helper;
	size_t	total;

	total = 0;
	if (s1)
		total += ft_strlen(s1);
	if (s2)
		total += ft_strlen(s2);
	ret = malloc ((total + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (s1 && s1[index] && index < ft_strlen(s1))
	{
		ret[index] = s1[index];
		index++;
	}
	helper = 0;
	while (s2 && s2[helper] && index < total)
		ret[index++] = s2[helper++];
	ret[index] = '\0';
	return (ret);
}
