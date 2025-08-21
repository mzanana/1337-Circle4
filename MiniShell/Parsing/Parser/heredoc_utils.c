#include "../../execution/exec.h"

int	open_tmpfile(char **tmp_path)
{
	int	fd;

	*tmp_path = make_tempfile();
	if (!tmp_path)
		return (-1);
	fd = open(*tmp_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("heredoc");
	return (fd);
}

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

void	sigint_handler_herdoc(int signal)
{
	(void)signal;
	g_herdoc_stop = true;
	status_set(130);
	rl_replace_line("", 0);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

char	*make_tempfile(void)
{
	char	*random;
	char	*full;
	int		fd;
	int		i;

	fd = -1;
	i = 1337;
	while (fd < 0 && i < INT_MAX)
	{
		random = ft_itoa(i);
		full = ft_strjoin2("/tmp/minishell_hd_", random);
		free(random);
		fd = open(full, O_CREAT | O_EXCL | O_WRONLY, 0644);
		if (fd > 0)
			break ;
		i++;
	}
	close(fd);
	return (full);
}

void	cleanup_heredocs(t_cmd *cmd)
{
	t_redir	*r;

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
