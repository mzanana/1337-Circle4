/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 03:44:51 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 03:44:53 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution/exec.h"

void	export_exit_(char *dst, int *i, int *j)
{
	char	*status_str;

	status_str = ft_itoa(status_get());
	write_val(dst, i, status_str);
	free(status_str);
	(*j) += 2;
}

void	expand_into_heredoc(char *dst, char *src, t_env *env)
{
	char	*key;

	int (i), (j), (k);
	i = ((j = 0), (k = 0), 0);
	while (src[j])
	{
		if (src[j] == '$' && src[j + 1] && \
			(var_start(src[j + 1]) || src[j + 1] == '?'))
		{
			if (src[j + 1] == '?')
				export_exit_(dst, &i, &j);
			else
			{
				k = 0;
				while (src[++j] && var_middle(src[j]))
					k++;
				key = ft_substr2(src, j - k, k);
				write_val(dst, &i, env_val(key, env));
			}
		}
		else
			dst[i++] = src[j++];
	}
	dst[i] = '\0';
}

char	*expand_heredoc(char *str, t_env *env)
{
	int		len;
	char	*buff;

	len = new_len(str, 1, env);
	buff = gc_calloc(sizeof(char) * len);
	if (!buff)
		return (NULL);
	expand_into_heredoc(buff, str, env);
	return (ft_strjoin2(buff, "\n"));
}
