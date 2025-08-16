
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

void	expand_into(char *dst, char *src, t_env *env)
{
	char	*key;
	
	int (i), (j), (sq), (dq), (k);
	i = 0;
	j = 0;
	sq = 0;
	dq = 0;

	while (src[j])
	{
		if ((src[j] == '\'' || src[j] == '"') &&  quote_checker(src[j], &sq, &dq, NULL)) (void)dq;
		if (src[j] == '$' && !sq && src[j + 1] && (var_start(src[j + 1]) || src[j + 1] == '?'))
		{
			if (src[j + 1] == '?')
			{
				write_val(dst, &i, ft_itoa(status_get()));
				j += 2;
			}
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

char *expand_it(char *str, t_env *env)
{
	int len;
	char *buff;
	
	len = new_len(str, env);
	buff = gc_calloc(sizeof(char) * len);
	if (!buff)
		return NULL;
	expand_into(buff, str, env);
	buff = remove_qoutes_if_needed(buff, (bool *)&len);
	return (buff);
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
