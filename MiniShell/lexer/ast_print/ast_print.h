/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:04:00 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/21 07:45:04 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_PRINT_H
# define AST_PRINT_H

# include "../parce.h"
# define INDENT_SIZE 8

void		print_cmd(t_cmd *ast);
void		print_cmd_redirection(t_cmd *ast, int indent);
void		print_cmd_simple_cmd(t_cmd *ast, int indent);
void		print_cmd_type(t_cmd *ast, int indent);

/* Internals */
void		_print_tree_end_root(int indent);
void		_print_cmd_helper(t_cmd *ast, int indent);
void		_tree_line_prefix(int indent, bool is_empty_line);

void	_print_ast_helper(t_cmd *ast, int indent);
/* type printings */
const char	*redir_type_to_str(t_redir_type type);
void	print_ast_simple_cmd(t_cmd *ast, int indent);


# define TEXT_RESET "\033[0m"

# define TEXT_BLACK "\033[0;30m"
# define TEXT_RED "\033[0;31m"
# define TEXT_GREEN "\033[0;32m"
# define TEXT_YELLOW "\033[0;33m"
# define TEXT_BLUE "\033[0;34m"
# define TEXT_PURPLE "\033[0;35m"
# define TEXT_CYAN "\033[0;36m"
# define TEXT_WHITE "\033[0;37m"

/* Bold */
# define TEXT_BBLACK "\033[1;30m"
# define TEXT_BRED "\033[1;31m"
# define TEXT_BGREEN "\033[1;32m"
# define TEXT_BYELLOW "\033[1;33m"
# define TEXT_BBLUE "\033[1;34m"
# define TEXT_BPURPLE "\033[1;35m"
# define TEXT_BCYAN "\033[1;36m"
# define TEXT_BWHITE "\033[1;37m"

/* Underline */
# define TEXT_UBLACK "\033[4;30m"
# define TEXT_URED "\033[4;31m"
# define TEXT_UGREEN "\033[4;32m"
# define TEXT_UYELLOW "\033[4;33m"
# define TEXT_UBLUE "\033[4;34m"
# define TEXT_UPURPLE "\033[4;35m"
# define TEXT_UCYAN "\033[4;36m"
# define TEXT_UWHITE "\033[4;37m"

/* Background */
# define TEXT_BG_BLACK "\033[40m"
# define TEXT_BG_RED "\033[41m"
# define TEXT_BG_GREEN "\033[42m"
# define TEXT_BG_YELLOW "\033[43m"
# define TEXT_BG_BLUE "\033[44m"
# define TEXT_BG_PURPLE "\033[45m"
# define TEXT_BG_CYAN "\033[46m"
# define TEXT_BG_WHITE "\033[47m"

#endif
