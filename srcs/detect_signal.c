/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 02:59:30 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 03:15:11 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_exit_code;

void	signal_handler(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == CHILD)
			printf("\n");
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_exit_code = 130;
	}
	else if (signo == SIGQUIT)
	{
		if (pid == CHILD)
			printf("Quit\n");
		g_exit_code = 131;
	}
}

void	detect_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
