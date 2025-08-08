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

int	apply_heredoc(t_redir *redir)
{
	int	fd;

	fd = handle_heredoc(redir->filename);
	if (fd == -1)
	{
		perror("heredoc");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	open_redirection_file(t_redir *redir)
{
	if (redir->type == R_INPUT)
		return (open(redir->filename, O_RDONLY));
	else if (redir->type == R_OUTPUT)
		return (open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (redir->type == R_APPAND)
		return (open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644));
	return (-1);
}

int	apply_file_redirection(t_redir *redir, int fd)
{
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
	return (0);
}
int	handle_redirections(t_redir *redir)
{
	int	fd;

	while (redir)
	{
		if (redir->type == R_HERDOC)//R_HEREDOC!
		{
			if (apply_heredoc(redir) == -1)
				return (-1);
		}
		else
		{
			fd = open_redirection_file(redir);
			if (apply_file_redirection(redir, fd) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}
