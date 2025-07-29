#include "../parsing_hf.h"


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
				cmd_fill(tmp, tokens->value);
				tokens = tokens->next;
			}
			else
			{
				red_fill(&(tmp->redir), tokens->type, tokens->next->value, tokens->is_quoted);
				tokens = tokens->next->next;
			}
		}
		cmd_add_back(&ret, tmp);
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	return (ret);
}


