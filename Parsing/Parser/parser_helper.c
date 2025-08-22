/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:20:37 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 00:20:38 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_hf.h"

t_redir	*redir_maker(t_token_type type, char *value, bool is_quoted)
{
	t_redir	*ret;

	ret = gc_calloc (sizeof (t_redir));
	ret->type = type;
	ret->filename = value;
	ret->quoted = is_quoted;
	ret->next = NULL;
	return (ret);
}

char	*heredoc_quote_remover(char *s, bool *quoted)
{
	char	*res;
	char	qoute;

	int (i), (j);
	i = 0;
	j = 0;
	res = gc_calloc(ft_strlen(s) + 1);
	if (!res || !s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			qoute = s[i++];
			*quoted = true;
			while (s[i] && s[i] != qoute)
				res[j++] = s[i++];
			if (s[i] == qoute)
				i++;
		}
		else
			res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}

t_cmd	*handle_heredoc(t_token **tokens, t_cmd *tmp)
{
	char	*redir_filename;
	bool	is_quoted;

	is_quoted = false;
	redir_filename = heredoc_quote_remover((*tokens)->next->value, &is_quoted);
	cmd_redir_fill(&(tmp->redir), (*tokens)->type, redir_filename, is_quoted);
	*tokens = (*tokens)->next->next;
	return (tmp);
}

t_cmd	*handle_other_redirection(t_token **tokens, t_env *env, t_cmd *tmp)
{
	char	*redir_filename;
	char	*resolved_path;

	redir_filename = expand_it((*tokens)->next->value, env);
	if (!(*tokens)->is_quoted && ft_strchr(redir_filename, '*'))
	{
		resolved_path = join_current_dir_redi(redir_filename);
		if (!resolved_path)
		{
			write(1, "minishell: ambiguous redirect\n", 30);
			return (NULL);
		}
		cmd_redir_fill(&(tmp->redir), (*tokens)->type, \
		resolved_path, (*tokens)->next->is_quoted);
	}
	else
		cmd_redir_fill(&(tmp->redir), (*tokens)->type, \
		redir_filename, (*tokens)->next->is_quoted);
	*tokens = (*tokens)->next->next;
	return (tmp);
}

t_cmd	*handle_redirection(t_token **tokens, t_env *env, t_cmd *tmp)
{
	if ((*tokens)->type == T_HEREDOC)
		return (handle_heredoc(tokens, tmp));
	else
		return (handle_other_redirection(tokens, env, tmp));
}
