/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:35:40 by ahwang            #+#    #+#             */
/*   Updated: 2025/11/27 18:04:57 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	check_echo_option(t_cmd *cmd)
{
	int	i;
	int	j;
	int	tmp;

	i = -1;
	while (cmd->option[++i])
	{
		j = 0;
		tmp = 0;
		if (ft_strncmp(cmd->option[i], "-n", ft_strlen("-n")))
		{
			if (i == 0)
				return (-1);
			return (i);
		}
		while (cmd->option[i][++j] == 'n')
			tmp++;
		if ((int)(ft_strlen(cmd->option[i])) - 1 != tmp)
		{
			if (i == 0)
				return (-1);
			return (i);
		}
	}
	return (i);
}

int	run_echo(t_cmd *cmd)
{
	int	n_option;
	int	flag_print;
	int	i;

	n_option = 0;
	while (cmd->option[n_option])
		n_option++;
	flag_print = check_echo_option(cmd);
	if (flag_print == n_option)
		return (g_exit = 0, cmd->exit = 0, 0);
	i = 0;
	if (flag_print != -1)
	{
		i = flag_print;
		while (cmd->option[i + 1])
			printf("%s ", cmd->option[i++]);
		if (cmd->option[i])
			printf("%s", cmd->option[i]);
		return (g_exit = 0, cmd->exit = 0, 0);
	}
	while (cmd->option[i + 1])
		printf("%s ", cmd->option[i++]);
	printf("%s", cmd->option[i]);
	printf("\n");
	return (g_exit = 0, cmd->exit = 0, 0);
}
