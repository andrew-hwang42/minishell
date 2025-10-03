/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:51:34 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 07:06:48 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	check_pid(t_cmd **cmd, char **env, int i, int exit_code)
{
	if (cmd[i]->pid == CHILD
		|| (cmd[i]->pid == PARENTS && is_same_str(cmd[i]->cmd, "exit")))
	{
		if (!exit_code)
			exit_code = cmd[i]->exit;
		free_cmd(cmd);
		free_2d_arr(env);
		exit(exit_code);
	}
}

void	run_command(t_cmd **cmd, char **env, int i)
{
	int	exit_code;

	exit_code = 0;
	if (is_same_str(cmd[i]->cmd, "echo"))
		run_echo(cmd[i]);
	// else if (is_same_str(cmd[i]->cmd, "cd"))
	// 	run_cd(cmd[i], env);
	else if (is_same_str(cmd[i]->cmd, "pwd"))
		run_pwd(cmd[i]);
	// else if (is_same_str(cmd[i]->cmd, "export"))
	// 	run_export(cmd[i], env);
	else if (is_same_str(cmd[i]->cmd, "unset"))
		run_unset(cmd[i], env);
	else if (is_same_str(cmd[i]->cmd, "env"))
		run_env(cmd[i], env);
	// else if (is_same_str(cmd[i]->cmd, "exit"))
	// 	run_exit(cmd[i]);
	else
		exit_code = run_non_builtin(cmd[i], env);
	check_pid(cmd, env, i, exit_code);
}
