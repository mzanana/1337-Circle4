#include "../parsing_hf.h"

int	count_args(t_cmd *cmd)
{
	int ret;

	if (!cmd->argv)
		return (0);
	ret = 0;
	while (cmd->argv[ret])
		ret++;
	return ret;
}

void	cmd_argv_fill(t_cmd *cmd, char *value)
{
	char	**new_argv;
	int		length;
	int		i;

	length = count_args(cmd);
	new_argv = gc_calloc(sizeof(char*) * (length + 2));
	if (!new_argv)
		return ;
	i = -1;
	while (cmd->argv[++i])
		new_argv[i] = cmd->argv[i];
	new_argv[length] = value;
	new_argv[length + 1] = NULL;
	cmd->argv = new_argv;
}


t_cmd *token_to_command(t_token *tokens)
{
	t_cmd	*ret;
	t_cmd	*tmp;

	ret = NULL;
	while (tokens)
	{
		tmp = gc_calloc(sizeof(t_cmd));
		while (tokens && tokens->type != T_PIPE)
		{
			if (tokens->type == T_WORD)
			{
				cmd_argv_fill(tmp, tokens->value);
				tokens = tokens->next;
			}
			else
			{
				cmd_redir_fill(&(tmp->redir), tokens->type, tokens->next->value, tokens->is_quoted);
				tokens = tokens->next->next;
			}
		}
		cmd_add_back(&ret, tmp);
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	return (ret);
}


