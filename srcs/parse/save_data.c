/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 03:23:21 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/28 03:42:36 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_cmd	**realloc_cmd(t_cmd **cmd, int i)
{
	cmd = ft_realloc(cmd, sizeof(t_cmd *) * (i + 1), sizeof(t_cmd *) * (i + 2));
	if (!cmd)
		return (err_msg("malloc error\n"), NULL);
	cmd[i] = (t_cmd *)ft_calloc(sizeof(t_cmd), 2);
	if (!cmd[i])
	{
		err_msg("malloc error\n");
		return (free_cmd(cmd), NULL);
	}
	return (cmd);
}

t_cmd	**save_data(t_cmd **cmd, char *cmd_splitted_pipe, int i)
{
	char	**cmd_with_option;
	int		cnt;

	cmd = realloc_cmd(cmd, i);
	if (!cmd)
		return (NULL);
	cmd_with_option = ft_split(cmd_splitted_pipe, ' ');
	cnt = 0;
	while (cmd_with_option[cnt])
		cnt++;
	if (!cnt)
	{
		free_cmd(cmd);
		return (free_2d_arr(cmd_with_option), NULL);
	}
	cmd[i]->cmd = ft_strdup(cmd_with_option[0]);
	cmd[i]->option = save_option(cmd_with_option + 1, cnt);
	cmd[i]->redir = save_redir(cmd_with_option + 1);
	if (!cmd[i]->cmd || !cmd[i]->option || !cmd[i]->redir)
	{
		free_cmd(cmd);
		return (free_2d_arr(cmd_with_option), NULL);
	}
	return (free_2d_arr(cmd_with_option), cmd);
}
