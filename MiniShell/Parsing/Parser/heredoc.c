#include "../../execution/exec.h"

bool	g_herdoc_stop = false;

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*ret;
	size_t	index;
	size_t	helper;
	size_t	total;

	total = 0;
	if (s1)
		total += ft_strlen(s1);
	if (s2)
		total += ft_strlen(s2);
	ret = gc_calloc ((total + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	index = 0;
	while (s1 && s1[index] && index < ft_strlen(s1))
	{
		ret[index] = s1[index];
		index++;
	}
	helper = 0;
	while (s2 && s2[helper] && index < total)
		ret[index++] = s2[helper++];
	ret[index] = '\0';
	return (ret);
}

void    sigint_handler_herdoc(int sig)
{
    (void)sig;
    g_herdoc_stop = true;
    status_set(130);
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_done = 1;  // cleanly stop readline loop immediately
}


char *make_tempfile(void)
{
	char *random;
	char *full;
	int fd;
	int i;

	fd = -1;
	i = 1337;
	while (fd < 0 && i < INT_MAX)
	{
		random = ft_itoa(i);
		full = ft_strjoin2("/tmp/minishell_hd_", random);
		free(random);
		fd = open(full, O_CREAT | O_EXCL | O_WRONLY, 0644);
		if (fd > 0)
			break;
		i++;
	}
	close(fd);
	return (full);
}

void    cleanup_heredocs(t_cmd *cmd)
{
    t_redir *r;
    
    while (cmd)
    {
        r = cmd->redir;
        while (r)
        {
            if (r->type == T_HEREDOC && r->is_temp)
            unlink(r->filename);
            r = r->next;
        }
        cmd = cmd->next;
    }
}

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

char *expand_heredoc(char *str, t_env *env)
{
	int len;
	char *buff;

	len = new_len(str, env);
	buff = gc_calloc(sizeof(char) * len);
	if (!buff)
		return NULL;
	expand_into_heredoc(buff, str, env);

	return (ft_strjoin2(buff, "\n"));
}


char    *read_heredoc(char *delimiter, bool expand, t_env *env)
{
    char    *line;
    char    *expanded;
    int fd;
    char    *tmp_path;
    
    tmp_path = make_tempfile();
    if (!tmp_path)
        return (NULL);
    fd = open(tmp_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("heredoc");
        return (NULL);
    }
    signal(SIGINT, sigint_handler_herdoc);
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            write(2, "minishell: warning: here-document delimited by end-of-file (wanted `", 68);
            write(2, delimiter, ft_strlen(delimiter));
            write(2, "`)\n", 3);
            break ;
        }
        if (g_herdoc_stop)
        {
            free(line);
            close(fd);
            unlink(tmp_path);
            setup_promt_signals();  // restore normal prompt signals
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();         // force immediate redisplay of main prompt
            return (NULL);
        }

        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break ;
        }
        if (expand)
            expanded = expand_heredoc(line, env);
        else
            expanded = ft_strjoin2(line, "\n");
        write(fd, expanded, ft_strlen(expanded));
        free(line);
    }
    close(fd);
    return (tmp_path);
}
bool    process_all_heredocs(t_cmd *cmd, t_env *env)
{
    t_redir *redir;
    char    *tmp_path;
    
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