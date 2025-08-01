#include "exec.h"

int	handle_heredoc(char *delimiter)
{
	int	pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	return(pipefd[0]);
}

int	handle_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == R_HERDOC)//heredoc
		{
			fd = handle_heredoc(redir->filename);
			if (fd == -1)
			{
				perror("heredoc");
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
		{
			fd = -1;
			if (redir->type == R_INPUT)
				fd = open(redir->filename, O_RDONLY);
			else if (redir->type == R_OUTPUT)
				fd = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (redir->type == R_APPAND)
				fd = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
			{
				perror(redir->filename);
				return (-1);
			}
			if (redir->type == R_INPUT)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		redir = redir->next;
	}
	return (0);
}

t_redir	*new_redir(t_redir_type type, char *filename)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	redir->next = NULL;
	return (redir);
}
