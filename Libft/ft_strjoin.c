/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 02:29:54 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 02:29:55 by anaamaja         ###   ########.fr       */
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
