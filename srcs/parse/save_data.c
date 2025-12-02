/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 03:23:21 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/02 09:07:39 by ahwang           ###   ########.fr       */
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

void	revert_echo_option(char *option_i)
{
	int	i;
	int	end;

	i = -1;
	while (option_i[++i])
	{
		if (option_i[i] == SINGLE_QUOTE || option_i[i] == DOUBLE_QUOTE)
		{
			end = find_char_pos(option_i, option_i[i], i + 1);
			option_i = remove_str_from_line(option_i, end, 1);
			option_i = remove_str_from_line(option_i, i, 1);
		}
		if (option_i[i] == SPACE_IN_QUOTE)
			option_i[i] = ' ';
		if (option_i[i] == REDIR_IN_QUOTE_IN)
			option_i[i] = '<';
		if (option_i[i] == REDIR_IN_QUOTE_OUT)
			option_i[i] = '>';
		if (option_i[i] == PIPE_IN_QUOTE)
			option_i[i] = '|';
	}
}

t_cmd	**save_data(t_cmd **cmd, char *cmd_splitted_pipe, int i)
{
	char	**cmd_with_option;
	int		cnt;
	int		cnt_option;

	cmd = realloc_cmd(cmd, i);
	if (!cmd)
		return (NULL);
	cmd_with_option = ft_split(cmd_splitted_pipe, ' ');
	cnt = 0;
	while (cmd_with_option[cnt])
		cnt++;
	if (!cnt)
		return (free_cmd(cmd), free_2d_arr(cmd_with_option), NULL);
	cmd[i]->cmd = ft_strdup(cmd_with_option[0]);
	cmd[i]->option = save_option(cmd_with_option + 1, cnt);
	cmd[i]->redir = save_redir(cmd_with_option + 1);
	if (!cmd[i]->cmd || !cmd[i]->option || !cmd[i]->redir)
		return (free_cmd(cmd), free_2d_arr(cmd_with_option), NULL);
	if (is_same_str(cmd[i]->cmd, "echo"))
	{
		cnt_option = -1;
		while (cmd[i]->option[++cnt_option])
			revert_echo_option(cmd[i]->option[cnt_option]);
	}
	return (free_2d_arr(cmd_with_option), cmd);
}
