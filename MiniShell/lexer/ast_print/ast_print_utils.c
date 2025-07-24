/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:03:57 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/21 08:59:25 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

/**
 * _print_ast_helper
	- print ast nodes and follow its childs recursively meant only to be
 * used internally with the ast printer
 *
 * @indent: current indentation
 * @ast: first ast node of the tree
 * Return: Nothing
 */
void	_print_ast_helper(t_cmd *ast, int indent)
{
	while (ast)
	{
		print_ast_simple_cmd(ast, indent);
		ast = ast->next;
	}
}

/**
 * _tree_line_prefix - print the line prefixes (tree lines), meant only to be
 * used internally with the ast printer
 *
 * @indent: current indentation
 * @is_empty_line: is there something to be added before this line ended or not
 * Return: Nothing
 */
void	_tree_line_prefix(int indent, bool is_empty_line)
{
	int	i;

	i = 0;
	while (i < indent)
	{
		if (i + 1 == indent && is_empty_line == false)
			printf("%*s├", INDENT_SIZE, "");
		else
			printf("%*s│", INDENT_SIZE, "");
		i++;
	}
	if (is_empty_line)
		printf("\n");
}

/**
 * _print_tree_end_root - prints the end root of ended node tree, meant only to
 * be used internally with the ast printer
 *
 * @indent: current indentation
 * Return: Nothing
 */
void	_print_tree_end_root(int indent)
{
	int	i;

	i = 0;
	while (i < indent)
	{
		printf("%*s│", INDENT_SIZE, "");
		i++;
	}
	printf("%*s╰", INDENT_SIZE, "");
	printf("\n");
}
