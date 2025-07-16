#include "exec.h"

int	create_pipe_if_needed(t_cmd *cmd, int pipefd[2])
{
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		return (1);
	}
	return (0);
}

pid_t	fork_and_check(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}

void	pipe_child(t_cmd *cmd, int in_fd, int pipefd[2])
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]); // wedon't read in child
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	handle_redirections(cmd->redir);
	execve(cmd->argv[0], cmd->argv, NULL);
	perror("execve");
	exit(1);
}

int	execute_pipeline(t_cmd *cmds)
{
	int	in_fd;
	int	fd[2];
	int	status;
	pid_t	pid;

	in_fd = 0;
	while (cmds)
	{
		create_pipe_if_needed(cmds, fd);
		pid = fork_and_check();
		if (pid == 0)
			pipe_child(cmds, in_fd, fd);
		else
		{
			if (in_fd != 0)
				close(in_fd);
			if (cmds->next)
			{
				close(fd[1]);// we don't write in parent;
				in_fd = fd[0];// save red for the next cmd;
			}
		}
		cmds = cmds->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	return (1);
}

int	main(void)
{
	t_cmd	*cmd1 = malloc(sizeof(t_cmd));
	t_cmd	*cmd2 = malloc(sizeof(t_cmd));
	t_cmd	*cmd3 = malloc(sizeof(t_cmd));

	cmd1->argv = ft_split("/bin/yes", ' ');
	cmd1->redir = NULL;
	cmd1->next = cmd2;

	cmd2->argv = ft_split("/usr/bin/head -c 1M", ' ');
	cmd2->redir = NULL;
	cmd2->next = cmd3;

	cmd3->argv = ft_split("/usr/bin/wc -l", ' ');
	cmd3->redir = NULL;
	cmd3->next = NULL;

	int	exit_code = execute_pipeline(cmd1);
	printf("Exit code: %d\n", exit_code);
	return (exit_code);
}
