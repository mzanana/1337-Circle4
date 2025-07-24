/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 14:08:19 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/24 12:36:35 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"
#include "../execution/exec.h"

char    *ft_strndup(char *str, size_t n)
{
        size_t  i;
        char    *dup;

        i = 0;
        while (str[i] && i < n)
                i++;
        dup = calloc((i + 1), (sizeof(char)));
        if (!dup)
                return (NULL);
        i = 0;
        while (str[i] && i < n)
        {
                dup[i] = str[i];
                i++;
        }
        dup[i] = '\0';
        return (dup);
}


char	*join_and_free_two(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

/*
 ** Collects and joins consecutive word-like tokens that are not separated by spaces.
 ** Expands environment variables when appropriate, except inside single-quoted tokens.
 **
 ** @param lexer - pointer to the current lexer state
 ** @return      - new allocated string representing the joined and processed word
 */

char	*collect_joined_words(t_lexer *lexer, t_env *env)
{
	char	*word;
	char	*if_var;
	char	*processed;
	t_token	next_tok;
	t_token	tok;

	word = ft_strdup("");
	while (1)
	{
		tok = lexer_next_token(lexer);
		if_var = ft_strndup(tok.literal, tok.len);
		if (tok.type == TOK_SINGLE || !ft_strchr(if_var, '$'))
			processed = if_var;
		else if (ft_strchr(if_var, '$'))
		{
			processed = expand_variable(if_var, env);
			free(if_var);
		}
		word = join_and_free_two(word, processed);
		next_tok = lexer_peek_next_token(lexer);
		if ((next_tok.type != TOK_WORD && next_tok.type != TOK_SINGLE
				&& next_tok.type != TOK_DOUBLE) || next_tok.space == true)
			break ;
	}
	return (word);
}
/*
** Parses and joins tokens that form the heredoc delimiter.
** Sets the expand flag to true if any token is double-quoted,
** which means variable expansion should be allowed in the heredoc.
**
** @param lexer  - pointer to the current lexer state
** @param expand - pointer to a flag set to true if expansion is needed
** @return       - new allocated string representing the heredoc delimiter
*/

char	*parse_heredoc_delim(t_lexer *lexer, bool *expand)
{
	char	*word;
	char	*processed;
	t_token	next_tok;
	t_token	tok;

	word = ft_strdup("");
	while (1)
	{
		tok = lexer_next_token(lexer);
		processed = ft_strndup(tok.literal, tok.len);
		if (tok.type == TOK_DOUBLE)
			*expand = true;
		word = join_and_free_two(word, processed);
		next_tok = lexer_peek_next_token(lexer);
		if ((next_tok.type != TOK_WORD && next_tok.type != TOK_SINGLE
				&& next_tok.type != TOK_DOUBLE) || next_tok.space == true)
			break ;
	}
	return (word);
}

int	check_for_red(t_token tok)
{
	if (tok.type == TOK_APPAND || tok.type == TOK_OUTPUT
		|| tok.type == TOK_INPUT || tok.type == TOK_HERDOC)
		return (1);
	return (0);
}

void redirect_del(t_token *tok, t_cmd *cmd, t_lexer *lexer, t_env *env)
{
	bool expand;

	expand = false;
	if (tok->type == TOK_HERDOC)
	{
		*tok = lexer_next_token(lexer);
		add_redirection(cmd, type_redir(tok), parse_heredoc_delim(lexer, &expand), expand);
	}
	else
	{
		*tok = lexer_next_token(lexer);
		add_redirection(cmd, type_redir(tok), collect_joined_words(lexer, env), expand);
	}
}

/*
 ** Parses the input from the lexer and builds a linked list of commands.
 ** Handles command arguments, redirections (including heredocs), and pipes.
 **
 ** @param lexer - pointer to the lexer containing the token stream
 ** @return      - pointer to the head t_cmd list
 */

t_cmd	*build_cmd_list(t_lexer *lexer, t_env *env)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	tok;

	head = create_cmd();
	cmd = head;
	while (1)
	{
		tok = lexer_peek_next_token(lexer);
		if (tok.type == TOK_WORD || tok.type == TOK_DOUBLE || tok.type == TOK_SINGLE)
			add_to_argv(cmd, collect_joined_words(lexer, env));
		else if (check_for_red(tok))
			redirect_del(&tok, cmd, lexer, env);
		else if (tok.type == TOK_PIPE)
		{
			cmd->next = create_cmd();
			cmd = cmd->next;
			tok = lexer_next_token(lexer);
		}
		else if (tok.type == TOK_NULL)
			break ;
	}
	return (head);
}
