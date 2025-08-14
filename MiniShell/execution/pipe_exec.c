#include "exec.h"

void	handle_parent_after_fork(t_cmd *cmd, int *in_fd, int fd[2])
{
	if(*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*in_fd = fd[0];// save read for the next cmd/child
	}
}

void	wait_for_pipeline(pid_t last_pid)
{
	int	status;
	pid_t	pid;

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
}

int	execute_pipeline(t_cmd *cmds, t_env **env)
{
	int	in_fd;
	int	fd[2];
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
			handle_parent_after_fork(cmds, &in_fd, fd);
		}
		cmds = cmds->next;
	}
	wait_for_pipeline(last_pid);
	return (status_get());
}
