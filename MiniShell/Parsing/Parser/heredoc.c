#include "../../execution/exec.h"

bool	g_herdoc_stop = false;

void	expand_into_heredoc(char *dst, char *src, t_env *env)
{
	char	*key;
	
	int (i), (j),(k);
	i = 0;
	j = 0;
    k = 0;

	while (src[j])
	{
		if (src[j] == '$' && src[j + 1] && (var_start(src[j + 1]) || src[j + 1] == '?'))
		{
			if (src[j + 1] == '?')
			{
				char	*status_str = ft_itoa(status_get());
				write_val(dst, &i, status_str);
				free(status_str);
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

char	*expand_heredoc(char *str, t_env *env)
{
	int		len;
	char	*buff;

	len = new_len(str, env);
	buff = gc_calloc(sizeof(char) * len);
	if (!buff)
		return (NULL);
	expand_into_heredoc(buff, str, env);
	return (ft_strjoin2(buff, "\n"));
}

bool	is_del(char *line, char *delimiter)
{
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (true);
	}
	return (false);
}

bool	handle_line(char *line, int fd, bool expand, t_env *env)
{
	char	*expanded;

	if (expand)
		expanded = expand_heredoc(line, env);
	else
		expanded = ft_strjoin2(line, "\n");
	write(fd, expanded, ft_strlen(expanded));
	free(line);
	return (true);
}

void	write_eof_warning(char *delimiter)
{
	write(2, "minishell: warning: here-document \
	delimited by end-of-file (wanted `", 68);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "`)\n", 3);
}

char	*read_heredoc(char *delimiter, bool expand, t_env *env)
{
	char	*line;
	int		fd;
	char	*tmp_path;

	fd = open_tmpfile(&tmp_path);
	if (fd < 0)
		return (NULL);
	signal(SIGINT, sigint_handler_herdoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write_eof_warning(delimiter);
			break ;
		}
		if (g_herdoc_stop)
			return (free(line), close(fd), unlink(tmp_path), NULL);
		if (is_del(line, delimiter))
			break ;
		if (!handle_line(line, fd, expand, env))
			break ;
	}
	close(fd);
	return (tmp_path);
}

bool	process_all_heredocs(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	char	*tmp_path;

	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == T_HEREDOC)
			{
				tmp_path = read_heredoc(redir->filename, !redir->quoted, env);
				if (!tmp_path)
					return (false);
				redir->is_temp = true;
				redir->filename = tmp_path;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (true);
}
