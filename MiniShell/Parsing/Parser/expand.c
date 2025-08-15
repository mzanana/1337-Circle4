#include "../parsing_hf.h"

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	index;

	if (!s || start > ft_strlen(s))
		return (ft_strdup(""));
	if ((len + start) < ft_strlen(s))
		ret = gc_calloc ((len + 1) * sizeof(char));
	else
		ret = gc_calloc ((ft_strlen(s) - start + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (index < len && s[start])
		ret[index++] = s[start++];
	ret[index] = '\0';
	return (ret);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int var_start(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int var_middle(char c)
{
	return (ft_isalnum(c) || c == '_');
}

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

char	*env_val(char *key, t_env *env)
{
	t_env	*e;

	e = env;
	while (e)
	{
		if (e->key && !ft_strcmp(e->key, key))
			return (e->value);
		e = e->next;
	}
	return (NULL);
}

int get_var_size(char *str, int i, int j, t_env *env)
{
	char *val;
	char *key;

	key = ft_substr2(str, i, j - i);
	val = env_val(key, env);
	if (!val)
		return (0);
	return (ft_strlen(val));
}
int	env_len(char *str, int *i, t_env *env)
{
	int ret;
	int j;

	ret = 1;
	j = *i + 1;
	while (str[j] && var_middle(str[j]))
	{
		ret++;
		j++;
	}
	ret = get_var_size(str, *i + 1, j, env) - ret;
	(*i) = j - 1;
	return (ret);
}

int	new_len(char *s, t_env *env)
{
	int	(i), (len), (sq), (dq);

	i = 0;
	len = ft_strlen(s) + 1;
	sq = 0;
	dq = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			quote_checker(s[i], &sq, &dq, &len);
		else if (s[i] == '$' && !sq && s[i + 1] && (var_start(s[i + 1]) || s[i + 1] == '?'))
				len += env_len(s, &i, env);
		i++;
	}
	return (len);
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
		if ((src[j] == '\'' || src[j] == '"') && \
		quote_checker(src[j], &sq, &dq, NULL))
			j++;
		else if (src[j] == '$' && !sq && src[j + 1] && (var_start(src[j + 1]) || src[j + 1] == '?'))
		{
			if (src[j + 1] == '?')
			{
				j += 2;
				printf ("^");
			}
			
			else 
			{
				k = 0;
				while (src[++j] && var_middle(src[j]))
					k++;
				key = ft_substr(src, j - k, k);
				// printf("%s\n", key);
				write_val(dst, &i, env_val(key, env));
			}
		}
		else
			dst[i++] = src[j++];
	}
	dst[i] = '\0';
}

void	ft_expand(t_cmd *cmd, t_env *env)
{
	int		i;
	int		j;
	int		len;
	char	*buf;

	while (cmd)
	{
		t_redir	*redir = cmd->redir;
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			len = new_len(cmd->argv[i], env);
			buf = gc_calloc(sizeof(char) * len);
			if (!buf)
				return ;
			expand_into(buf, cmd->argv[i], env);
			cmd->argv[i] = buf;
			// printf("%s", cmd->argv[i]);
			i++;
		}
		while (redir)
		{
			j = 0;
			if (redir->filename && ft_strchr(redir->filename, '$'))
			{
				len = new_len(redir->filename, env);
				buf = gc_calloc(sizeof(char) * len);
				if (!buf)
					return ;
				expand_into(buf, redir->filename, env);
				redir->filename = buf;
				j++;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}
// '' '' "" '' "" '"' "'" $USER$$$USER "$USER" '$USER' '"$USER"' "'$USER'"