/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 07:05:21 by ahwang            #+#    #+#             */
/*   Updated: 2025/11/26 18:35:49 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	run_pwd(t_cmd *cmd)
{
	char	buf[1024];

	if (cmd->option[0])
		return (g_exit = 2, cmd->exit = 2,
			minishell_err_msg("pwd", "invalid option"), 2);
	getcwd(buf, sizeof(buf));
	if (errno == ERANGE)
		return (g_exit = 1, cmd->exit = 1,
			minishell_err_msg("pwd: cannot access directory",
				"No such file or directory"), 1);
	return (printf("%s\n", buf), g_exit = 0, cmd->exit = 0, 0);
}

int	run_unset(t_cmd *cmd, char ***env)
{
	int	i;
	int	j;

	if (!cmd->option[0])
		return (g_exit = 0, cmd->exit = 0, 0);
	if (cmd->option[0][0] == '-')
		return (g_exit = 2, cmd->exit = 2,
			minishell_err_msg("unset", "invalid option"), 2);
	i = -1;
	while (cmd->option[++i])
	{
		j = -1;
		while ((*env)[++j])
		{
			if (!ft_strncmp((*env)[j], cmd->option[i],
				ft_strlen(cmd->option[i]))
				&& (*env)[j][ft_strlen(cmd->option[i])] == '=')
			{
				*env = remove_from_env(*env, cmd->option[i]);
				j--;
			}
		}
	}
	return (g_exit = 0, cmd->exit = 0, 0);
}

int	run_env(t_cmd *cmd, char **env)
{
	int	i;

	if (cmd->option[0])
		return (g_exit = 125, cmd->exit = 125,
			minishell_err_msg("env", "invalid option"), 125);
	i = -1;
	while (env[++i])
	{
		if (find_char_pos(env[i], '=', 0) != -1)
			printf("%s\n", env[i]);
	}
	return (g_exit = 0, cmd->exit = 0, 0);
}

int	run_exit(t_cmd *cmd)
{
	if (cmd->pid == PARENTS)
		ft_putstr_fd("exit\n", STDERR);
	if (!cmd->option[0])
		return (g_exit = 0, cmd->exit = 0, 0);
	if (!(is_numeric_str(cmd->option[0])
			&& LONG_MIN < ft_atolonglong(cmd->option[0])
			&& ft_atolonglong(cmd->option[0]) < LONG_MAX))
		return (g_exit = 2, cmd->exit = 2,
			minishell_err_msg("exit", "numeric argument required"), 2);
	if (cmd->option[1])
		return (g_exit = 1, cmd->exit = 1,
			minishell_err_msg("exit", "too many arguments"), 1);
	return (g_exit = ft_atolonglong(cmd->option[0]),
		cmd->exit = ft_atolonglong(cmd->option[0]),
		ft_atolonglong(cmd->option[0]));
}
