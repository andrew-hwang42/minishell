/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 03:16:17 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/28 03:42:26 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_cmd	**parse(t_cmd **cmd, char **env, char *line)
{
	char	*new_line;
	char	**split_cmd;
	int		i;

	if (!check_parse_err(line, cmd))
		return (free(line), NULL);
	new_line = apply_env_var(env, line);
	new_line = make_space_near_redir(new_line);
	if (!new_line)
		return (free(line), NULL);
	split_cmd = ft_split(new_line, '|');
	free(new_line);
	i = -1;
	while (split_cmd[++i])
	{
		cmd = save_data(cmd, split_cmd[i], i);
		if (!cmd)
			return (free_2d_arr(split_cmd), NULL);
	}
	free(line);
	free_2d_arr(split_cmd);
	return (cmd);
}
