/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 03:50:18 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 06:44:33 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	wait_for_child_process(t_cmd **cmd)
{
	int	i;
	int	last;
	int	status;

	last = 0;
	while (cmd[last])
		last++;
	i = -1;
	while (++i < last - 1)
		if (cmd[i]->pid > 0)
			waitpid(cmd[i]->pid, NULL, 0);
	if (cmd[last - 1]->pid != PARENTS && cmd[last - 1]->pid > 0)
	{
		waitpid(cmd[last - 1]->pid, &status, 0);
		if (WIFEXITED(status))
		{
			g_exit = WEXITSTATUS(status);
			if (!g_exit)
				g_exit = cmd[last - 1]->exit;
		}
		else if (WIFSIGNALED(status))
			g_exit = 128 + WTERMSIG(status);
	}
	else
		g_exit = cmd[last - 1]->exit;
}

void	check_fork_set_fd(t_cmd **cmd, int i, int (*fd)[2])
{
	if (!is_builtin(cmd[i]->cmd) || cmd[i + 1] || i > 0)
		cmd[i]->pid = fork();
	else
		cmd[i]->pid = PARENTS;
	if (cmd[i]->pid == PARENTS)
	{
		(*fd)[STDIN] = dup(STDIN);
		(*fd)[STDOUT] = dup(STDOUT);
	}
}

void	revert_close_fd(int (*fd)[2])
{
	dup2((*fd)[STDIN], STDIN);
	dup2((*fd)[STDOUT], STDOUT);
	close((*fd)[STDIN]);
	close((*fd)[STDOUT]);
}

int	execute(t_cmd **cmd, char **env, int (**my_pipe)[2], int (*fd)[2])
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		check_fork_set_fd(cmd, i, fd);
		if (cmd[i]->pid == CHILD || cmd[i]->pid == PARENTS)
		{
			handle_pipe(cmd, my_pipe, i);
			if (!set_fd_redir(cmd[i]))
			{
				if (cmd[i]->pid == CHILD)
					exit(1);
				if (cmd[i]->pid == PARENTS || cmd[i]->pid > 0)
					revert_close_fd(fd);
				return (g_exit = 1, 0);
			}
			run_command(cmd, env, i);
			if (cmd[i]->pid == CHILD)
				exit(cmd[i]->exit);
			revert_close_fd(fd);
		}
	}
	return (1);
}

int	execute_main(t_cmd **cmd, char **env)
{
	int	(*my_pipe)[2];
	int	fd[2];
	int	len;

	my_pipe = NULL;
	if (!check_heredoc(cmd))
		return (0);
	if (!create_pipe(cmd, &my_pipe))
		return (0);
	if (!execute(cmd, env, &my_pipe, &fd))
		return (close_pipe(cmd, &my_pipe), free(*my_pipe), 0);
	close_pipe(cmd, &my_pipe);
	free(*my_pipe);
	len = 0;
	while (cmd[len])
		len++;
	if (len)
		wait_for_child_process(cmd);
	return (1);
}
