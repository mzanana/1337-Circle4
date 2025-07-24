/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:09:42 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/03 18:36:06 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	token_word(t_lexer *lexer)
{
	t_token	tok;

	tok.literal = &lexer->input[lexer->pos];
	tok.len = 0;
	while (lexer->c && lexer->c != '|' && lexer->c != '<' && lexer->c != '>'
		&& lexer->c != '\'' && lexer->c != '\"' && !ft_isspace(lexer->c))
	{
		tok.len++;
		read_char(lexer);
	}
	tok.type = TOK_WORD;
	return (tok);
}

t_token	token_s_d_word(t_lexer *lexer)
{
	t_token	tok;
	char	c;

	if (lexer->c == '\'')
		c = '\'';
	else
		c = '\"';
	read_char(lexer);
	tok.literal = &lexer->input[lexer->pos];
	tok.len = 0;
	while (lexer->c && lexer->c != c)
	{
		tok.len++;
		read_char(lexer);
	}
	if (lexer->c == '\0')
	{
		tok.type = TOK_INVALID;
		return (tok);
	}
	read_char(lexer);
	tok.type = toke_type(c);
	return (tok);
}

t_token	token_redir(t_lexer *lexer)
{
	t_token	tok;

	if (lexer->c == '<')
	{
		if (lexer->input[lexer->read_pos] == lexer->c)
		{
			tok = token_new(&lexer->input[lexer->pos], TOK_HERDOC, 2);
			read_char(lexer);
		}
		else
			tok = token_new(&lexer->input[lexer->pos], TOK_INPUT, 1);
	}
	else
	{
		if (lexer->input[lexer->read_pos] == lexer->c)
		{
			tok = token_new(&lexer->input[lexer->pos], TOK_APPAND, 2);
			read_char(lexer);
		}
		else
			tok = token_new(&lexer->input[lexer->pos], TOK_OUTPUT, 1);
	}
	read_char(lexer);
	return (tok);
}

/*
 ** Gets the next token from the lexer input.
 ** Skips any whitespace and define the token type
 ** based on the current character in the input.
 **
 ** @param lexer - pointer to the lexer structure tracking the input from readline
 ** @return      - the next token
 */

t_token	lexer_next_token(t_lexer *lexer)
{
	t_token	tok;
	bool	space;

	space = skip_white_space(lexer);
	if (lexer->c == '>' || lexer->c == '<')
		tok = token_redir(lexer);
	else if (lexer->c == '|')
	{
		tok = token_new(&lexer->input[lexer->pos], TOK_PIPE, 1);
		read_char(lexer);
	}
	else if (lexer->c == '\0')
		tok = token_new(NULL, TOK_NULL, 0);
	else if (lexer->c == '\'' || lexer->c == '\"')
		tok = token_s_d_word(lexer);
	else
		tok = token_word(lexer);
	tok.space = space;
	return (tok);
}

/*
 ** Peeks at the next token without advancing the lexer.
 ** Creates a copy of the current lexer.
 ** then restores the original lexer state.
 **
 ** @param lexer - pointer to the current lexer
 ** @return      - the next token without consuming the lexer,
 */

t_token	lexer_peek_next_token(t_lexer *lexer)
{
	t_lexer	prev_lexer;
	t_token	tok;

	prev_lexer = *lexer;
	tok = lexer_next_token(lexer);
	*lexer = prev_lexer;
	return (tok);
}
