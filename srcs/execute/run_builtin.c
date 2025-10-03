/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 07:05:21 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 07:22:44 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	run_echo(t_cmd *cmd)
{
	int	i;
	int	tmp;
	int	option_n;

	option_n = 0;
	if (!ft_strncmp(cmd->option[0], "-n", ft_strlen("-n")))
	{
		i = 0;
		tmp = 0;
		while (cmd->option[0][++i] == 'n')
			tmp++;
		if ((int)(ft_strlen(cmd->option[0])) - 1 == tmp)
			option_n++;
	}
	i = 0;
	if (option_n)
		i++;
	while (cmd->option[i + 1])
		printf("%s ", cmd->option[i++]);
	printf("%s", cmd->option[i]);
	if (!option_n)
		printf("\n");
	cmd->exit = 0;
}

void	run_pwd(t_cmd *cmd)
{
	char	buf[1024];

	getcwd(buf, sizeof(buf));
	if (errno == ERANGE)
	{
		minishell_err_msg("pwd: cannot access directory",
			"No such file or directory");
		cmd->exit = 1;
	}
	else
		printf("%s\n", buf);
	cmd->exit = 0;
}

void	run_unset(t_cmd *cmd, char **env)
{
	int	i;
	int	j;
	int	k;

	if (cmd->option[0])
	{
		i = -1;
		while (cmd->option[++i])
		{
			j = -1;
			while (env[++j])
			{
				if (!ft_strncmp(env[j], cmd->option[i],
						ft_strlen(cmd->option[i]))
					&& env[j][ft_strlen(cmd->option[i])] == '=')
				{
					free(env[j]);
					k = j - 1;
					while (env[++k])
						env[k] = env[k + 1];
				}
			}
		}
	}
	cmd->exit = 0;
}

void	run_env(t_cmd *cmd, char **env)
{
	int	i;

	if (cmd->option[0])
	{
		minishell_err_msg("env", "unrecognized option");
		cmd->exit = 125;
		return ;
	}
	i = -1;
	while (env[++i])
	{
		if (find_char_pos(env[i], '=', 0) != -1)
			printf("%s\n", env[i]);
	}
	cmd->exit = 0;
}
