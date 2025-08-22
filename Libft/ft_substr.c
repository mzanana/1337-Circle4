/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 02:30:06 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 02:30:07 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	index;

	if (!s || start > ft_strlen(s))
		return (ft_strdup(""));
	if ((len + start) < ft_strlen(s))
		ret = malloc ((len + 1) * sizeof(char));
	else
		ret = malloc ((ft_strlen(s) - start + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (index < len && s[start])
		ret[index++] = s[start++];
	ret[index] = '\0';
	return (ret);
}
