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

void	pipe_child(t_cmd *cmd, int in_fd, int pipefd[2], t_env **env)
{
	int	exit_code;
	char	*path;

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
	if (handle_redirections(cmd->redir))
		exit(1);
	if (is_builtin(cmd->argv[0]))
	{
		exit_code = run_builtin(cmd, env);
		exit(exit_code);
	}
	path = find_cmd_path(cmd->argv[0], *env);
	if (!path)
	{
		write(2, "Command not found\n", 19);
		exit(127);
	}
	execve(path, cmd->argv, NULL);
	perror("execve");
	free(path);
	exit(1);
}

int	execute_pipeline(t_cmd *cmds, t_env **env)
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
			pipe_child(cmds, in_fd, fd, env);
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
		status_set(WEXITSTATUS(status));
	else
		status_set(1);
	return (status_get());
}

int	run_command(t_cmd *cmds, t_env **env)
{
	if (is_single_builtin(cmds))
	{
		status_set(run_builtin(cmds, env));
		return (status_get());
	}
	else
		return (execute_pipeline(cmds, env));
}

/*int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*env = init_env_list(envp);
	t_cmd	*cmd1 = malloc(sizeof(t_cmd));
	//t_cmd	*cmd2 = malloc(sizeof(t_cmd));
	//t_cmd	*cmd3 = malloc(sizeof(t_cmd));

	//t_redir	*redir = malloc(sizeof(t_redir));

	cmd1->argv = ft_split("export &&=lal", ' ');
	cmd1->redir = NULL;
	cmd1->next = NULL;

	cmd2->argv = ft_split("echo hello world", ' ');
	cmd2->redir = redir;
	cmd2->next = NULL;

	redir->type = R_OUTPUT;
	redir->filename = ft_strdup("testing");
	redir->next = NULL;

	cmd3->argv = ft_split("wc -l", ' ');
	cmd3->redir = NULL;
	cmd3->next = NULL;

	int	last_status = 1;
	run_command(cmd1, &env, &last_status);
	free_env_list(env);
	return (0);
}*/
