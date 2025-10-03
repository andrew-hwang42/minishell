/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:51:34 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 09:23:49 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	check_pid(t_cmd **cmd, char **env, int i, int exit_code)
{
	if (cmd[i]->pid == CHILD
		|| (cmd[i]->pid == PARENTS
			&& is_same_str(cmd[i]->cmd, "exit")))
	{
		if (!exit_code)
			exit_code = cmd[i]->exit;
		if (cmd[i]->pid == PARENTS
			&& is_same_str(cmd[i]->cmd, "exit")
			&& cmd[i]->option[1] && exit_code == 1)
			return ;
		free_cmd(cmd);
		free_2d_arr(env);
		exit(exit_code);
	}
}

void	run_command(t_cmd **cmd, char **env, int (*fd)[2], int i)
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
	else if (is_same_str(cmd[i]->cmd, "exit"))
		exit_code = run_exit(cmd[i]);
	else
		exit_code = run_non_builtin(cmd[i], env);
	if (cmd[i]->pid == PARENTS
		&& is_same_str(cmd[i]->cmd, "exit")
		&& (!cmd[i]->option[1] || (cmd[i]->option[1] && exit_code == 2)))
		revert_close_fd(fd);
	check_pid(cmd, env, i, exit_code);
}
