#include "exec.h"

int	open_redirection_file(t_redir *redir)
{
	if (redir->type == T_HEREDOC)
		return (open(redir->filename, O_RDONLY));
	if (redir->type == T_REDIR_IN)
		return (open(redir->filename, O_RDONLY));
	else if (redir->type == T_REDIR_OUT)
		return (open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	else if (redir->type == T_APPEND)
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
	if (redir->type == T_REDIR_IN || redir->type == T_HEREDOC)
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
		fd = open_redirection_file(redir);
			if (apply_file_redirection(redir, fd) == -1)
				return (-1);
		redir = redir->next;
	}
	return (0);
}
