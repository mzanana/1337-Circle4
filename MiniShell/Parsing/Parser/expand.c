
#include "../../execution/exec.h"

int	quote_checker(char c, int *sq, int *dq, int *cnt)
{
	if (c == '\'' && !(*dq))
	{
		*sq = !(*sq);
		if (cnt)
			(*cnt)--;
		return (1);
	}
	if (c == '"' && !(*sq))
	{
		*dq = !(*dq);
		if (cnt)
			(*cnt)--;
		return (1);
	}
	return (0);
}

void	write_val(char *dst, int *i, char *val)
{
	int	x;

	if (!val)
		return ;
	x = 0;
	while (val[x])
	{
		dst[*i] = val[x];
		(*i)++;
		x++;
	}
}

void	expand_into(char *dst, char *src,char *map, char *nmap, t_env *env)
{
	char	*key;
	
	int (i), (j), (sq), (dq), (k);
	i = 0;
	j = 0;
	sq = 0;
	dq = 0;
	int e = 0; // for map
	int f = 0; // for nmap

	while (src[j])
	{
		quote_checker(src[j], &sq, &dq, NULL);
		if (src[j] == '$' && !sq && src[j + 1] && (var_start(src[j + 1]) || src[j + 1] == '?'))
		{
			if (src[j + 1] == '?')
			{
				char	*status_str = ft_itoa(status_get());
				// printf("\n\n%s\n\n", status_str);
				write_val(dst, &i, status_str);
				k = 0;
				while (k < ft_strlen(status_str))
				{
					nmap[f++] = '0';
					k++;
				}
				j += 2;
				e += 2;
				free(status_str);
			}
			else 
			{
				k = 0;
				while (src[++j] && var_middle(src[j]))
					k++;
				e += k + 1;
 				key = ft_substr2(src, j - k, k);
				k = ft_strlen(env_val(key, env));
				int d=0;
				while (d < k)
				{
					nmap[f++] = '0';
					d++;
				}
				write_val(dst, &i, env_val(key, env));
			}
		}
		else
		{
			nmap[f++] = map[e++];
			dst[i++] = src[j++];
		}
	}
	// printf("\nmap -> %s\nnmap -> %s\n", map, nmap);
	nmap[f] = '\0';
	dst[i] = '\0';
}
char *ft_strdup2(char *s)
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

char *ft_map(char *str)
{
	int i = 0;
	int sq = 0;
	int dq = 0;
	char *map = ft_strdup2(str);

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

char *expand_it(char *str, t_env *env)
{
	int len;
	char *buff;
	char *ret;
	char *map;
	char *nmap;

	map = ft_map(str);
		// printf("\n%s\n", map);
	len = new_len(str, env);
	nmap = gc_calloc(sizeof(char) * len);
	buff = gc_calloc(sizeof(char) * len);
	if (!buff)
		return NULL;
	expand_into(buff, str, map, nmap, env);
	// printf("\n%s\n", buff);
	ret = remove_qoutes_if_needed(buff, nmap);
	// printf("\n%s",ret);
	return (ret);
}


void	ft_expand(t_cmd *cmd, t_env *env)
{
	int		i;
	t_redir *red_walk;

	while (cmd)
	{
		red_walk = cmd->redir;
		while (red_walk)
		{
			if (red_walk->type != T_HEREDOC)
				red_walk->filename = expand_it(red_walk->filename, env);
			red_walk = red_walk->next;
		}
		i = -1;
		while (cmd->argv && cmd->argv[++i])
			cmd->argv[i] = expand_it(cmd->argv[i], env);

		cmd = cmd->next;
	}

}
