/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 01:58:05 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 01:58:06 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_hf.h"

static bool	handle_operator_increment(t_token *new_token, int *i)
{
	if (new_token->type == T_PIPE || new_token->type == T_REDIR_IN
		|| new_token->type == T_REDIR_OUT)
		(*i)++;
	else if (new_token->type == T_APPEND || new_token->type == T_HEREDOC)
		(*i) += 2;
	return (true);
}

bool	handle_operator_token(t_token **tokens, char *input, int *i)
{
	t_token	*new_token;

	new_token = NULL;
	if (input[*i] == '|')
		new_token = token_new(ft_strndup("|", 1), T_PIPE, 0);
	else if (input[*i] == '<' && input[*i + 1] == '<')
		new_token = token_new(ft_strndup("<<", 2), T_HEREDOC, 0);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		new_token = token_new(ft_strndup(">>", 2), T_APPEND, 0);
	else if (input[*i] == '<')
		new_token = token_new(ft_strndup("<", 1), T_REDIR_IN, 0);
	else
		new_token = token_new(ft_strndup(">", 1), T_REDIR_OUT, 0);
	if (!new_token)
		return (false);
	handle_operator_increment(new_token, i);
	token_add_back(tokens, new_token);
	return (true);
}

char	*append_char_to_buffer(char *buffer, char c)
{
	char	*new_buf;
	size_t	len;
	size_t	i;

	if (!buffer)
		len = 0;
	else
		len = ft_strlen(buffer);
	new_buf = gc_calloc(len + 2);
	if (!new_buf)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_buf[i] = buffer[i];
		i++;
	}
	new_buf[i++] = c;
	new_buf[i] = '\0';
	return (new_buf);
}

static void	print_unexpected_eof(char quote)
{
	write(2, "minishell: unexpected EOF while looking for matching `", 54);
	write(2, &quote, 1);
	write(2, "'\n", 2);
}

bool	append_quoted_segment(char **buffer, char *input, int *i)
{
	char	quote;

	quote = input[*i];
	*buffer = append_char_to_buffer(*buffer, quote);
	(*i)++;
	while (input[*i])
	{
		*buffer = append_char_to_buffer(*buffer, input[*i]);
		if (!(*buffer))
			return (false);
		if (input[*i] == quote)
		{
			(*i)++;
			return (true);
		}
		(*i)++;
	}
	print_unexpected_eof(quote);
	return (false);
}
