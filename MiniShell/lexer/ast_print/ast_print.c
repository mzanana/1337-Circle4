/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:03:51 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/21 09:06:10 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

void	print_ast_redirection(t_cmd *ast, int indent);
void	print_ast_type(t_cmd *ast, int indent);
/**
 * print_ast_simple_cmd - print ast simple command, with its I/O redirections
 *
 * @indent: give it 0 if you're not printing a tree
 * Return: Noting
 */
void	print_ast_simple_cmd(t_cmd *ast, int indent)
{
	size_t	i;
	size_t	count = 0;

	print_ast_type(ast, indent++);
	i = 0;
	count = 0;
	while (ast->argv && i < (size_t)ast->argv[count])
		count++;
	_tree_line_prefix(indent, true);
	_tree_line_prefix(indent, false);
	printf("────── %sARGS (%ld):%s ", TEXT_UWHITE, (long)count, TEXT_RESET);
	if (count == 0)	
		printf("(nil)");
	i = 0;
	while (ast->argv && i < (size_t)ast->argv[i])
		printf("`%s` ", ast->argv[i++]);
	printf("\n");
	_tree_line_prefix(indent, false);
	printf("────── %sI/O (%zu):%s ", TEXT_UWHITE, (long) 69, TEXT_RESET);
	print_ast_redirection(ast, indent);
	_tree_line_prefix(indent, true);
}

/**
 * print_ast_type - print type of an ast node
 *
 * @ast: Pointer to ast node
 * @indent: give it 0 if your not printing a tree
 * Return: Noting
 */
void	print_ast_type(t_cmd *ast, int indent)
{
	(void) ast;
	_tree_line_prefix(indent, false);
	printf("%s", TEXT_BGREEN);
	printf("◯───── %s\n", "COMMAND");
	printf("%s", TEXT_RESET);
}


/**
 * print_ast_redirection - print ast I/O redirections
 *
 * @ast: Pointer to none-null ast node
 * @indent: give it 0 if your not printing a tree
 * Return: Nothing
 */
void	print_ast_redirection(t_cmd *ast, int indent)
{
	t_redir *walk;
	
	(void)indent;

	int i = 0;
	if (ast->redir == NULL)
		printf("(nil)");	
	walk = ast->redir;
	while (walk)
	{
		if (i % 2)
			printf("%s", TEXT_RED);
		else
			printf("%s", TEXT_BBLUE);
		printf("%s '%s'%s ", redir_type_to_str(walk->type), walk->filename, TEXT_RESET);
		walk = walk->next;
		i++;
	}
	printf("\n");
}


/**
 * print_ast - Enjoy a nice view of your beautiful ast
 *
 * @ast: Pointer to none-null ast node
 * Return: Nothing
 */
void	print_ast(t_cmd *cmd)
{
	if (!cmd)
	{
		printf("Empty cmd\n");
		return ;
	}
	_print_ast_helper(cmd, 0);
	_print_tree_end_root(0);
}
