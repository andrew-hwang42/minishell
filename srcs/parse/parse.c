/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 03:16:17 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 06:27:57 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_cmd	**parse(t_cmd **cmd, char **env, char *line)
{
	// char	*new_line;
	// char	**split_pipe;
	// int		i;

	if (!check_parse_err(line, cmd))
		return (NULL);
(void)env;
	// new_line = make_new_line(env, rdline);
	// split_pipe = ft_split(new_line, '|');
	// free(new_line);
	// i = -1;
	// while (split_pipe[++i])
	// {
	// 	cmd = alloc_cmd(cmd, i);
	// 	if (!cmd)
	// 		return (free_2d_arr(split_pipe), NULL);
	// 	cmd = fill_cmd_struct(cmd, split_pipe[i], i);
	// 	if (!cmd)
	// 		return (free_2d_arr(split_pipe), NULL);
	// }
	// free_2d_arr(split_pipe);
	// free(line);
	return (cmd);
}
