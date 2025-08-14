#include "exec.h"

void	setup_pipes_child(int in_fd, t_cmd *cmd, int pipefd[2])
{
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);// This connects stdin of this child to the previous pipe’s read-end
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);// This connects stdout of this child to the current pipe’s write-end
		close(pipefd[1]);
	}
}

void	exec_builtin_child(t_cmd *cmd, t_env **env)
{
	int	exit_code;

	exit_code = run_builtin_child(cmd, env);
	exit(exit_code);
}

void	pipe_child(t_cmd *cmd, int in_fd, int pipefd[2], t_env **env)
{
	char (*path), (**real_envp);
	setup_pipes_child(in_fd, cmd, pipefd);
	if (handle_redirections(cmd->redir))
		exit(1);
	if (!cmd->argv)
		exit(0);
	if (is_builtin(cmd->argv[0]))
		exec_builtin_child(cmd, env);
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
