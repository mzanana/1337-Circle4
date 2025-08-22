/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 02:29:35 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 02:29:37 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	w_cnt(char const *str, char ch);
static size_t	ft_lenght(const char *str, char ch, size_t start);
static char		*ft_fill(char *dst, char const *src, size_t len, size_t *from);
static void		ft_free(char **ret, size_t place);

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	j;
	size_t	i;
	size_t	k;

	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * (w_cnt(s, c) + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	k = 0;
	while (s[i])
	{
		j = ft_lenght(s, c, i);
		ret[k] = ft_fill(ret[k], s, j, &i);
		if (!ret[k])
			return (ft_free(ret, k), NULL);
		while (s[i] && s[i] == c)
			i++;
		k++;
	}
	return ((ret[k] = 0), ret);
}

static void	ft_free(char **ret, size_t place)
{
	while (place--)
		free(ret[place]);
	free(ret);
}

static size_t	w_cnt(char const *str, char ch)
{
	size_t	cnt;
	size_t	i;
	size_t	flag;

	cnt = 0;
	i = 0;
	while (str[i] && str[i] == ch)
		i++;
	flag = 1;
	if (str[i])
		cnt++;
	while (str[i])
	{
		if (str[i] != ch && flag == 0)
		{
			cnt++;
			flag = 1;
		}
		if (str[i] == ch && flag == 1)
			flag = 0;
		i++;
	}
	return (cnt);
}

static size_t	ft_lenght(const char *str, char ch, size_t start)
{
	size_t	i;
	size_t	cnt;

	i = start;
	cnt = 0;
	while (str[i] && str[i] != ch)
	{
		i++;
		cnt++;
	}
	return (cnt);
}

static char	*ft_fill(char *dst, char const *src, size_t len, size_t *from)
{
	size_t	index;

	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	index = 0;
	while (index < len)
	{
		dst[index] = src[*from];
		index++;
		*from += 1;
	}
	dst[index] = '\0';
	return (dst);
}
