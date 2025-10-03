/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:04:30 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 14:28:09 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	export_without_option(char **env)
{
	char	*key;
	char	*value;
	int		i;

	i = -1;
	while (env[++i])
	{
		key = ft_substr(env[i], 0, find_char_pos(env[i], '=', 0) + 1);
		value = ft_substr(env[i], find_char_pos(env[i], '=', 0) + 1,
				ft_strlen(env[i]) - find_char_pos(env[i], '=', 0) + 1);
		printf("declare -x %s\"%s\"\n", key, value);
		free(key);
		free(value);
	}
}

void	export_with_option(char ***env, char *option)
{
	char	*key;
	int		i;

	if (find_char_pos(option, '=', 0) == -1)
		return ;
	key = ft_substr(option, 0, find_char_pos(option, '=', 0));
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], key, ft_strlen(key))
			&& (*env)[i][ft_strlen(key)] == '=')
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(option);
			free(key);
			return ;
		}
	}
	free(key);
	i = 0;
	while ((*env)[i])
		i++;
	*env = ft_realloc(*env, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	(*env)[i] = ft_strdup(option);
}

int	run_export(t_cmd *cmd, char ***env)
{
	int	i;
	int	j;

	if (!cmd->option[0])
		return (export_without_option(*env), g_exit = 0, cmd->exit = 0, 0);
	if (cmd->option[0][0] == '-')
		return (g_exit = 2, cmd->exit = 2,
			minishell_err_msg("export", "invalid option"), 2);
	i = -1;
	while (cmd->option[++i])
	{
		if (!(ft_isalpha(cmd->option[i][0]) || cmd->option[i][0] == '_'))
			return (g_exit = 1, cmd->exit = 1,
				minishell_err_msg("export", "not a valid identifier"), 1);
		j = 0;
		while (cmd->option[i][++j])
		{
			if (!(ft_isalnum(cmd->option[i][j]) || cmd->option[i][j] == '='
				|| cmd->option[i][j] == '-' || cmd->option[i][j] == '_'))
				return (g_exit = 1, cmd->exit = 1,
					minishell_err_msg("export", "not a valid identifier"), 1);
		}
		export_with_option(env, cmd->option[i]);
	}
	return (g_exit = 0, cmd->exit = 0, 0);
}
