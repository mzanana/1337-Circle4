#include "../parsing_hf.h"

void	cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd	*handle_word_token(t_token **tokens, t_env *env, t_cmd *tmp)
{
	(*tokens)->value = expand_it((*tokens)->value, env);
	if (!(*tokens)->is_quoted && ft_strchr((*tokens)->value, '*'))
	{
		if (!join_current_dir(tmp, (*tokens)->value))
			cmd_argv_fill(tmp, (*tokens)->value);
	}
	else if ((*tokens)->value[0] == '\0' && !(*tokens)->is_quoted)
		;
	else
		cmd_argv_fill(tmp, (*tokens)->value);
	*tokens = (*tokens)->next;
	return (tmp);
}

t_cmd	*tokens_to_commands_helper(t_token **tokens, t_env *env, t_cmd *tmp)
{
	while (*tokens && (*tokens)->type != T_PIPE)
	{
		if ((*tokens)->type == T_WORD)
			tmp = handle_word_token(tokens, env, tmp);
		else
			tmp = handle_redirection(tokens, env, tmp);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

t_cmd	*tokens_to_commands(t_token *tokens, t_env *env)
{
	t_cmd	*ret;
	t_cmd	*tmp;

	ret = NULL;
	while (tokens)
	{
		tmp = gc_calloc(sizeof(t_cmd));
		tmp = tokens_to_commands_helper(&tokens, env, tmp);
		if (!tmp)
			return (NULL);
		cmd_add_back(&ret, tmp);
		if (tokens && tokens->type == T_PIPE)
			tokens = tokens->next;
	}
	return (ret);
}
