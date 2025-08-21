#include "../parsing_hf.h"

void	cmd_redir_fill(t_redir **redir, t_token_type type, \
	char *value, bool is_quoted)
{
	t_redir	*curr;
	t_redir	*holder;

	if (!*redir)
	{
		*redir = redir_maker(type, value, is_quoted);
		return ;
	}
	curr = *redir;
	while (curr->next)
		curr = curr->next;
	holder = redir_maker(type, value, is_quoted);
	curr->next = holder;
}

int	count_args(t_cmd *cmd)
{
	int	ret;

	if (!cmd->argv)
		return (0);
	ret = 0;
	while (cmd->argv[ret])
		ret++;
	return (ret);
}

void	cmd_argv_fill(t_cmd *cmd, char *value)
{
	char	**new_argv;
	int		length;
	int		i;

	length = count_args(cmd);
	new_argv = gc_calloc(sizeof(char *) * (length + 2));
	if (!new_argv)
		return ;
	if (cmd->argv)
	{
		i = -1;
		while (cmd->argv[++i])
			new_argv[i] = cmd->argv[i];
	}
	new_argv[length] = value;
	new_argv[length + 1] = NULL;
	cmd->argv = NULL;
	cmd->argv = new_argv;
}
