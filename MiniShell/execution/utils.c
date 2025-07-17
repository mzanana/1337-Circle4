#include "exec.h"

void	free_env_list(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

int	is_single_builtin(t_cmd *cmd)
{
	return (cmd && !cmd->next && is_builtin(cmd->argv[0]));
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo") 
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

int	run_builtin(t_cmd *cmd, t_env **env)
{
	if (!cmd | !cmd->argv | !cmd->argv[0])
		return (1);
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (ft_echo(cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "cd"))
		return (ft_cd(cmd->argv));
	if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->argv[0], "export"))
		return (ft_export(cmd->argv, env));
	if (!ft_strcmp(cmd->argv[0], "unset"))
		return (ft_unset(cmd->argv, env));
	if (!ft_strcmp(cmd->argv[0], "env"))
		return (ft_env(cmd->argv, *env));
	if (!ft_strcmp(cmd->argv[0], "exit"))
		return (ft_exit(cmd->argv, 0));
	return (1);
}
