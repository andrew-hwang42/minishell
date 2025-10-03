/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:51:34 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 03:56:54 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	check_pid(t_cmd **cmd, char **env, int i)
{
	if (cmd[i]->pid == CHILD
		|| (cmd[i]->pid == PARENTS && is_same_str(cmd[i]->cmd, "exit")))
	{
		i = cmd[i]->exit;
		free_cmd(cmd);
		free_2d_arr(env);
		exit(i);
	}
}

void	run_command(t_cmd **cmd, char **env, int i)
{
	// if (is_same_str(cmd[i]->cmd, "echo"))
	// 	run_echo();
	// else if (is_same_str(cmd[i]->cmd, "cd"))
	// 	run_cd();
	// else if (is_same_str(cmd[i]->cmd, "pwd"))
	// 	run_pwd();
	// else if (is_same_str(cmd[i]->cmd, "export"))
	// 	run_export();
	// else if (is_same_str(cmd[i]->cmd, "unset"))
	// 	run_unset();
	// else if (is_same_str(cmd[i]->cmd, "env"))
	// 	run_env();
	// else if (is_same_str(cmd[i]->cmd, "exit"))
	// 	run_exit();
	// else
	run_non_builtin(cmd[i], env);
	check_pid(cmd, env, i);
}
