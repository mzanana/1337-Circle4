/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:20:14 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 02:07:20 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../execution/exec.h"

bool	g_herdoc_stop = false;

bool	is_del(char *line, char *delimiter)
{
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (true);
	}
	return (false);
}

void	write_eof_warning(char *delimiter)
{
	write (2, "minishell: warning: here-document \
	delimited by end-of-file (wanted `", 68);
	write (2, delimiter, ft_strlen(delimiter));
	write (2, "`)\n", 3);
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
