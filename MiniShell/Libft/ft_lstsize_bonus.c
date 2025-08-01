/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:09:39 by mzanana           #+#    #+#             */
/*   Updated: 2024/11/22 02:05:24 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	ret;

	if (!lst)
		return (0);
	ret = 0;
	while (lst)
	{
		ret++;
		lst = lst -> next;
	}
	return (ret);
}
