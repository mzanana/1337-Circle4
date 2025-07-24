/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:15:17 by hfakou            #+#    #+#             */
/*   Updated: 2025/07/22 11:23:25 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parce.h"
#include "lexer.h"


void	print_error(char *pointer, size_t size)
{
	write(2, "minishell: syntax error near unexpeted token `", 47);
	write(2, pointer, size);
	write(2, "`\n", 2);
	g_exit_status = 2;
}

void	print_newline_error(void)
{
	write(2, "minishell: syntax error near unexpeted token `", 47);
	write(2, "newline", 7);
	write(2, "`\n", 2);
	g_exit_status = 2;
}
	
int	check_errors(t_lexer *lexer, t_token curr)
{
	t_token	n_tok;

	n_tok = lexer_peek_next_token(lexer);
	if (curr.type == TOK_PIPE && n_tok.type == TOK_NULL)
	{
		print_error(curr.literal, curr.len);
		return (1);
	}
	else if (check_for_red(curr))
	{
		if (n_tok.type == TOK_NULL)
		{
			print_newline_error();
			return (1);
		}
		else if (not_token(n_tok))
			return (1);
		else
			return (0);
	}
	else if (curr.type == TOK_PIPE && n_tok.type == TOK_PIPE)
	{
		print_error(n_tok.literal, n_tok.len);
		return (1);
	}
	return (0);
}

int	check_first_tok(t_token *token)
{
	if (token->type == TOK_PIPE)
	{
		token->type = TOK_NULL;
		write(2, "minishell: syntax error near unexpeted token `|`", 49);
		write(2, "\n", 1);
		g_exit_status = 2;
		return (1);
	}
	else
		return (0);
}

int	find_error(t_lexer lexer, char *input)
{
	t_token	tok;

	if (input[0] == '\0')
		return (1);
	lexer = lexer_new(input);
	tok = lexer_next_token(&lexer);
	if (check_first_tok(&tok))
		return (1);
	while (tok.type)
	{
		if (tok.type == TOK_INVALID)
		{
			write(2, "UNMATCHED QUOTE\n", 17);
			return (1);
		}
		else if (check_errors(&lexer, tok) == 1)
			return (1);
		tok = lexer_next_token(&lexer);
	}
	return (0);
}
