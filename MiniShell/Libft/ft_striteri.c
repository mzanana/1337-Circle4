/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:17:44 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/18 22:29:43 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		index;

	if (!s || !f)
		return ;
	index = ft_strlen(s);
	index = -1;
	while (s[++index])
		f((unsigned int)index, &s[index]);
}
