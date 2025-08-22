/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:21:52 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 00:21:53 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	print_err(char *msg1, char *path, char *msg2)
{
	write(2, msg1, ft_strlen(msg1));
	write(2, path, ft_strlen(path));
	write(2, msg2, ft_strlen(msg2));
}

int	check_executable(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			print_err("minishell: ", path, ": Is a directory\n");
			exit(126);
		}
		if (access(path, X_OK) == -1)
		{
			print_err("minishell: ", path, ": Permission denied\n");
			exit(126);
		}
	}
	else
	{
		print_err("minishell: ", path, ": No such file or directory\n");
		exit(127);
	}
	return (0);
}

int	create_pipe_if_needed(t_cmd *cmd, int pipefd[2])
{
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		return (1);
	}
	return (0);
}

pid_t	fork_and_check(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	return (pid);
}
