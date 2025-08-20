#include "exec.h"

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

int	run_single_builtin(t_cmd *cmds, t_env **env)
{
	int	saved_in;
	int	saved_out;

	save_stdio(&saved_in, &saved_out);
	if (cmds->redir && handle_redirections(cmds->redir))
	{
		restore_stdio(saved_in, saved_out);
		return (status_set(1), 1);
	}
	if (!ft_strcmp(cmds->argv[0], "exit"))
	{
		restore_stdio(saved_in, saved_out);
		ft_exit(cmds->argv, status_get());
	}
	status_set(run_builtin(cmds, env));
	restore_stdio(saved_in, saved_out);
	return (status_get());
}

int	run_command(t_cmd *cmds, t_env **env)
{
	if (!cmds->argv || !cmds->argv[0])
	{
		if (!cmds->next)
		{
			if (cmds->redir && redir_with_no_cmd(cmds->redir))
				return (status_set(1), 1);
			return (status_set(0), 0);
		}
	}
	if (cmds->argv && is_single_builtin(cmds))
		return (run_single_builtin(cmds, env));
	return (execute_pipeline(cmds, env));
}
