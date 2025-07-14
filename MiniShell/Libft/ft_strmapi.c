/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:22:16 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/18 21:46:45 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	int		index;

	if (!s)
		return (ft_strdup(""));
	if (s && !f)
		return (ft_strdup(s));
	index = ft_strlen(s);
	ret = malloc ((index + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = -1;
	while (s[++index])
		ret[index] = f((unsigned int)index, s[index]);
	ret[index] = '\0';
	return (ret);
}
