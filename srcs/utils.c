/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:57:55 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 04:45:19 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	err_msg(char *msg)
{
	ft_putstr_fd(RED, STDERR);
	ft_putstr_fd("Error: ", STDERR);
	ft_putstr_fd(BLACK, STDERR);
	ft_putstr_fd(msg, STDERR);
	ft_putstr_fd("\n", STDERR);
}

void	free_2d_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_cmd(t_cmd **cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i]->cmd)
			free(cmd[i]->cmd);
		if (cmd[i]->option)
			free_2d_arr(cmd[i]->option);
		j = -1;
		if (cmd[i]->redir)
		{
			while (cmd[i]->redir[++j])
			{
				if (cmd[i]->redir[j]->file)
					free(cmd[i]->redir[j]->file);
				free(cmd[i]->redir[j]);
			}
			free(cmd[i]->redir);
		}
		free(cmd[i]);
	}
	if (cmd)
		free(cmd);
}

void	exit_program(t_cmd **cmd, char **env, char *msg)
{
	if (cmd)
		free_cmd(cmd);
	if (env)
		free_2d_arr(env);
	if (msg)
		err_msg(msg);
}
