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
	char	**real_envp;

	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]); // we don't read in child
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (handle_redirections(cmd->redir))
		exit(1);
	if (!cmd->argv)
		exit(0);
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
	real_envp = env_to_envp(*env);
	execve(path, cmd->argv, real_envp);
	perror("execve");
	free_envp_array(real_envp);
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
	int	saved_stdin;
	int	saved_stdout;

	if (cmds->argv && is_single_builtin(cmds) && !ft_strcmp(cmds->argv[0], "exit"))
		ft_exit(cmds->argv, status_get());
	if (cmds->argv && is_single_builtin(cmds))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (handle_redirections(cmds->redir))
		{
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			status_set(1);
			return (1);
		}
		status_set(run_builtin(cmds, env));
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
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

	t_redir	*redir = malloc(sizeof(t_redir));

	cmd1->argv = ft_split("echo hello", ' ');
	cmd1->redir = redir;
	cmd1->next = NULL;

	//cmd2->argv = ft_split("echo hello world", ' ');
	//cmd2->redir = redir;
	//cmd2->next = NULL;

	redir->type = R_OUTPUT;
	redir->filename = ft_strdup("testing");
	redir->next = NULL;

	//cmd3->argv = ft_split("wc -l", ' ');
	//cmd3->redir = NULL;
	//cmd3->next = NULL;

	run_command(cmd1, &env);
	free_env_list(env);
	return (0);
}*/
