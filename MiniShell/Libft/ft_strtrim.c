/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 06:28:30 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/17 18:17:17 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	is_found(const char *str, char c)
{
	size_t	x;

	x = 0;
	while (str[x])
		if (str[x++] == c)
			return (1);
	return (0);
}

static size_t	ft_checker(const char *str, char const *trim)
{
	size_t	i;

	if (!str || !*str)
		return (1);
	i = 0;
	while (str[i] && is_found(trim, str[i]))
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	start;
	size_t	end;
	size_t	index;

	if (!set && s1)
		return (ret = ft_strdup(s1));
	if ((!s1 && !set) || ft_checker(s1, set))
		return (ft_strdup(""));
	index = 0;
	while (s1[index] && is_found(set, s1[index]))
		index++;
	start = index;
	index = ft_strlen(s1) - 1;
	while (s1[index] && is_found(set, s1[index]))
		index--;
	end = index;
	ret = malloc ((end - start + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (start <= end)
		ret[index++] = s1[start++];
	ret[index] = '\0';
	return (ret);
}
