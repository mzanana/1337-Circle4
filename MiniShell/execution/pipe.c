#include "exec.h"

void	print_err(char *msg1, char *path, char *msg2)
{
	write(2, msg1, ft_strlen(msg1));
	write(2, path, ft_strlen(path));
	write(2, msg2, ft_strlen(msg2));
}

int	check_executable(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			print_err("bash: ", path, ": Is a directory\n");
			exit(126);
		}
		if (access(path, X_OK) == -1)
		{
			print_err("bash: ", path, ": Permission denied\n");
			exit(126);
		}
	}
	else
	{
		print_err("bash: ", path, ": No such file or directory\n");
		exit(127);
	}
	return (0);
}

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
		print_err("bash: ", cmd->argv[0], ": command not found\n");
		exit(127);
	}
	real_envp = env_to_envp(*env);
	check_executable(path);
	execve(path, cmd->argv, real_envp);
	perror("execve");
	free_envp_array(real_envp);
	free(path);
	exit(126);
}

int	execute_pipeline(t_cmd *cmds, t_env **env)
{
	int	in_fd;
	int	fd[2];
	int	status;
	pid_t	pid;
	pid_t	last_pid;

	in_fd = 0;
	last_pid = 0;
	while (cmds)
	{
		create_pipe_if_needed(cmds, fd);
		pid = fork_and_check();
		if (pid == 0)
			pipe_child(cmds, in_fd, fd, env);
		else
		{
			last_pid = pid;
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
	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				status_set(WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				status_set(128 + WTERMSIG(status));
		}
	}
	return (status_get());
}

void	skip_empty_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	if (!cmd->argv)
		return ;
	i = 0;
	while (cmd->argv[i] && cmd->argv[i][0] == '\0')
		i++;
	if (!cmd->argv[i])
	{
		cmd->argv[0] = NULL;
		return ;
	}
	j = 0;
	while (cmd->argv[i])
		cmd->argv[j++] = cmd->argv[i++];
	cmd->argv[j] = NULL;
}

void	save_stdio(int *in, int *out)
{
	*in = dup(STDIN_FILENO);
	*out = dup(STDOUT_FILENO);
}

void	restore_stdio(int in, int out)
{
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

int	redir_with_no_cmd(t_redir *redir)
{
	int	saved_in;
	int	saved_out;

	save_stdio(&saved_in, &saved_out);
	if (redir && handle_redirections(redir))
	{
		restore_stdio(saved_in, saved_out);
		return (1);
	}
	restore_stdio(saved_in, saved_out);
	return (0);
}

int	run_command(t_cmd *cmds, t_env **env)
{
	int (saved_in), (saved_out);
	skip_empty_cmd(cmds);
	if (!cmds->argv || !cmds->argv[0])
	{
		if (cmds->redir && redir_with_no_cmd(cmds->redir))
			return(status_set(1), 1);
		return (status_set(0), 0);
	}
	if (cmds->argv && is_single_builtin(cmds) && !ft_strcmp(cmds->argv[0], "exit"))
		ft_exit(cmds->argv, status_get());
	if (cmds->argv && is_single_builtin(cmds))
	{
		save_stdio(&saved_in, &saved_out);
		if (cmds->redir && handle_redirections(cmds->redir))
		{
			restore_stdio(saved_in, saved_out);
			status_set(1);
			return (1);
		}
		status_set(run_builtin(cmds, env));
		restore_stdio(saved_in, saved_out);
		return (status_get());
	}
	return (execute_pipeline(cmds, env));
}
