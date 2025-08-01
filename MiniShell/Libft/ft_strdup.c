/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:43:03 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/18 17:38:40 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	len;
	int		index;

	len = ft_strlen(s);
	ret = (char *)malloc ((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = -1;
	while (s[++index])
		ret[index] = s[index];
	ret[index] = '\0';
	return (ret);
}
