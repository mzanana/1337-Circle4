/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:40:39 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/23 13:40:42 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	token_new(char *s, t_token_type type, size_t len)
{
	t_token	tok;

	tok.literal = s;
	tok.type = type;
	tok.len = len;
	return (tok);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

bool	skip_white_space(t_lexer *lexer)
{
	bool	found;

	found = 0;
	while (ft_isspace(lexer->c))
	{
		read_char(lexer);
		found = 1;
	}
	return (found);
}

t_token_type	toke_type(char c)
{
	if (c == '\'')
		return (TOK_SINGLE);
	else
		return (TOK_DOUBLE);
}
