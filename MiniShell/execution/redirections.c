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
		if (redir->type == R_HEREDOC)
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

/*int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	pid_t	pid;
	t_redir	*redir = NULL;
	
	//redir = new_redir(R_HEREDOC, "lala");
	redir = new_redir(R_INPUT, "lala.txt");
	redir->next = new_redir(R_OUTPUT, "hello.txt");
	redir->next->next = new_redir(R_APPAND, "test.c");
	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections(redir) != 0)
		{
			perror("redirection");
			write(2, "redirection failed\n", 20);
			exit(1);
		}
		char	*cmd[] = {"/bin/cat", NULL};
		execve(cmd[0], cmd, envp);
		perror("execev");
		exit(1);
	}
	else
		wait(NULL);
}*/
