/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:05:29 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 14:28:20 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	update_old_new_pwd(char ***env, char *new_pwd)
{
	char	*old_pwd;
	int		i;

	*env = remove_from_env(*env, "OLDPWD");
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], "PWD", 3)
			&& (*env)[i][ft_strlen("PWD")] == '=')
		{
			old_pwd = ft_strjoin("OLD", (*env)[i]);
			free((*env)[i]);
			(*env)[i] = old_pwd;
		}
	}
	*env = ft_realloc(*env, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	(*env)[i] = ft_strjoin("PWD=", new_pwd);
}

int	change_directory(t_cmd *cmd, char ***env, char *path)
{
	char	*tmp;
	char	new_pwd[1024];

	if (chdir(path) == -1)
	{
		tmp = ft_strjoin("cd: ", path);
		if (access(path, F_OK) == 0)
			return (g_exit = 1, cmd->exit = 1,
				minishell_err_msg(tmp, "Not a directory"),
				free(tmp), free(path), 1);
		else
			return (g_exit = 1, cmd->exit = 1,
				minishell_err_msg(tmp, "No such file or directory"),
				free(tmp), free(path), 1);
	}
	getcwd(new_pwd, sizeof(new_pwd));
	if (new_pwd[0])
		update_old_new_pwd(env, new_pwd);
	return (g_exit = 0, cmd->exit = 0, free(path), 0);
}

int	run_cd(t_cmd *cmd, char ***env)
{
	char	*home;
	int		i;

	if (cmd->option[0] && cmd->option[0][0] == '-')
		return (g_exit = 2, cmd->exit = 2,
			minishell_err_msg("cd", "invalid option"), 2);
	if (cmd->option[1])
		return (g_exit = 1, cmd->exit = 1,
			minishell_err_msg("cd", "too many arguments"), 1);
	if (!cmd->option[0])
	{
		home = NULL;
		i = -1;
		while ((*env)[++i])
			if (!ft_strncmp((*env)[i], "HOME", ft_strlen("HOME"))
				&& (*env)[i][ft_strlen("HOME")] == '=')
				home = ft_strdup((*env)[i]);
		if (!home)
			return (g_exit = 1, cmd->exit = 1,
				minishell_err_msg("cd", "HOME not set"), 1);
		home = remove_str_from_line(home, 0, ft_strlen("HOME") + 1);
		return (change_directory(cmd, env, home));
	}
	return (change_directory(cmd, env, ft_strdup(cmd->option[0])));
}
