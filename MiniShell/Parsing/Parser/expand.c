/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzanana <mzanana@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:20:27 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 03:12:58 by mzanana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution/exec.h"

char	*ft_strdup2(char *s)
{
	char	*ret;
	size_t	len;
	int		index;

	len = ft_strlen(s);
	ret = (char *)gc_calloc ((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = -1;
	while (s[++index])
		ret[index] = s[index];
	ret[index] = '\0';
	return (ret);
}

void	expand_into(char *dst, char *src, t_exp_vars *vars, t_env *env)
{
	while (src[vars->j])
	{
		quote_checker(src[vars->j], &vars->sq, &vars->dq, NULL);
		if (src[vars->j] == '$' && !vars->sq && src[vars->j + 1] && \
			(var_start(src[vars->j + 1]) || src[vars->j + 1] == '?'))
		{
			if (src[vars->j + 1] == '?')
				handle_exit_status(dst, vars);
			else
				handle_variable_expansion(dst, src, vars, env);
		}
		else
			fill_nmap_and_dst(dst, src, vars);
	}
	vars->nmap[vars->f] = '\0';
	dst[vars->i] = '\0';
}

char	*ft_map(char *str)
{
	char	*map;

	int (i), (sq), (dq);
	i = ((sq = 0), (dq = 0), 0);
	map = ft_strdup2(str);
	while (map[i])
	{
		if (quote_checker(map[i], &sq, &dq, 0))
			map[i] = '1';
		else
			map[i] = '0';
		i++;
	}
	return (map);
}

char	*remove_qoutes_if_needed(char *s, char *nmap)
{
	char	*res;

	int (i), (j);
	i = 0;
	j = 0;
	while (nmap && nmap[i])
	{
		if (nmap[i] == '1')
			j++;
		i++;
	}
	res = gc_calloc(ft_strlen(s) - j + 1);
	if (!res || !s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (nmap[i] == '1')
			i++;
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

char	*expand_it(char *str, t_env *env)
{
	int			len;
	char		*buff;
	char		*ret;
	t_exp_vars	vars;

	vars.map = ft_map(str);
	len = new_len(str, 0, env);
	vars.nmap = gc_calloc(sizeof(char) * len);
	buff = gc_calloc(sizeof(char) * len);
	if (!buff)
		return (NULL);
	vars.i = ((vars.j = 0), (vars.sq = 0), (vars.dq = 0), \
	(vars.k = 0), (vars.e = 0), (vars.f = 0), 0);
	expand_into(buff, str, &vars, env);
	ret = remove_qoutes_if_needed(buff, vars.nmap);
	return (ret);
}
