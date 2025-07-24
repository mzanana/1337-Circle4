/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:31:18 by hfakou            #+#    #+#             */
/*   Updated: 2025/06/27 22:51:34 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parce.h"

void	add_to_argv(t_cmd *cmd, char *arg)
{
	int	count;
	char	**new_argv;
	int	i;

	if (!arg)
		return ;
	count = 0;
	while (cmd->argv && cmd->argv[count])
		count++;
	new_argv = malloc(sizeof(char *) * (count + 2));
	if (!new_argv)
		return ;
	i = 0;
	while (i < count)
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[count] = arg;
	new_argv[count + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_redirection(t_cmd *cmd, t_redir_type type, char *file, bool expand)
{
	t_redir	*walk;
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	redir->type = type;
	redir->filename = file;
	redir->expand = expand;
	redir->next = NULL;
	if (!cmd->redir)
	{
		cmd->redir = redir;
		return ;
	}
	walk = cmd->redir;
	while (walk->next)
		walk = walk->next;
	walk->next = redir;
}

void ft_red_printf(t_redir_type type, char *name)
{
	if (type == R_HERDOC)
		printf("R_HERDOC {%s}\n", name);
	else if (type == R_OUTPUT)
		printf("R_OUTPUT {%s}\n", name);
	else if (type == R_INPUT)
		printf("R_INPUT {%s}\n", name);
	else if (type == R_APPAND)
		printf("R_APPAND {%s}\n", name);
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd	*walk;
	int		i;

	walk = cmd;
	printf("-------------------\n");
	while (walk)
	{
		i = 0;
		if (walk->argv)
		{
			while (walk->argv[i])
			{
				printf("%s\n", walk->argv[i]);
				i++;
			}
		}
		t_redir *walk_redirect;
		walk_redirect = walk->redir;
		while (walk_redirect)
		{
			ft_red_printf(walk_redirect->type, walk_redirect->filename);
			printf("herdok value : [%d]\n", walk_redirect->expand);
			walk_redirect = walk_redirect->next;
		}
		walk = walk->next;
		if (walk)
			printf("\n  --- PIPE -------------------\n\n");
	}
	printf("-------------------\n");
}

void	free_t_cmd(t_cmd *cmd)
{
	int		i;
	t_cmd	*walk;
	t_redir	*redir_tmp;

	while (cmd)
	{
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		while (cmd->redir)
		{
			free(cmd->redir->filename);
			redir_tmp = cmd->redir;
			cmd->redir = cmd->redir->next;
			free(redir_tmp);
		}
		walk = cmd;
		cmd = cmd->next;
		free(walk);
	}
}

t_redir_type	type_redir(t_token *token)
{
	if (token->type == TOK_HERDOC)
		return (R_HERDOC);
	else if (token->type == TOK_INPUT)
		return (R_INPUT);
	else if (token->type == TOK_OUTPUT)
		return (R_OUTPUT);
	else if (token->type == TOK_APPAND)
		return (R_APPAND);
	else
		return (0);
}
