
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
				j += 2;
				write_val(dst, &i, "0");
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
	return (buff);
}


void	ft_expand(t_cmd *cmd, t_env *env)
{
	int		i;
	// int		j;
	// int		len;
	// char	*buf;

	// while (cmd)
	// {
	// 	t_redir	*redir = cmd->redir;
	// 	i = 0;
	// 	while (cmd->argv && cmd->argv[i])

	while (cmd)
	{
		i = -1;
		while (cmd->argv && cmd->argv[++i])
			cmd->argv[i] = expand_it(cmd->argv[i], env);
		while (cmd->redir)
		{
			if (!cmd->redir->quoted)
				cmd->redir->filename = expand_it(cmd->redir->filename, env);
			cmd->redir = cmd->redir->next;
		}
		// while (redir)
		// {
		// 	j = 0;
		// 	if (redir->filename && ft_strchr(redir->filename, '$'))
		// 	{
		// 		len = new_len(redir->filename, env);
		// 		buf = gc_calloc(sizeof(char) * len);
		// 		if (!buf)
		// 			return ;
		// 		expand_into(buf, redir->filename, env);
		// 		redir->filename = buf;
		// 		j++;
		// 	}
		// 	redir = redir->next;
		// }
		cmd = cmd->next;
	}
}
