/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 01:58:29 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 01:58:30 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing_hf.h"

void	print_unexpected_token(const char *token)
{
	size_t	token_len;

	token_len = ft_strlen(token);
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, token, token_len);
	write(2, "'\n", 2);
}

void	print_unexpected_newline(void)
{
	write(2, "minishell: syntax error near unexpected token `newline`\n", 57);
}

bool	is_redirection(t_token_type type)
{
	return (type == T_REDIR_IN || type == T_REDIR_OUT \
		|| type == T_APPEND || type == T_HEREDOC);
}
