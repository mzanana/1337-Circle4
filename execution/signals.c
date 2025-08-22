/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaamaja <anaamaja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:22:05 by anaamaja          #+#    #+#             */
/*   Updated: 2025/08/22 00:22:06 by anaamaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	status_set(130);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_promt_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
