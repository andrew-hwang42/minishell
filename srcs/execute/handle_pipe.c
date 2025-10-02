/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 04:17:57 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/02 21:01:21 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	create_pipe(t_cmd **cmd, int (**my_pipe)[2])
{
	int	i;

	i = 0;
	*my_pipe = NULL;
	while (cmd[i + 1])
	{
		*my_pipe = ft_realloc(*my_pipe,
				sizeof(**my_pipe) * i, sizeof(**my_pipe) * (i + 1));
		if (!*my_pipe)
			return (err_msg("malloc error"), 0);
		if (pipe((*my_pipe)[i]) == -1)
			return (err_msg("pipe error"), 0);
		i++;
	}
	return (1);
}

void	close_pipe(t_cmd **cmd, int (**my_pipe)[2])
{
	int	i;

	i = 0;
	while (cmd[i + 1])
	{
		close((*my_pipe)[i][STDIN]);
		close((*my_pipe)[i][STDOUT]);
		i++;
	}
}

void	handle_pipe(t_cmd **cmd, int (**my_pipe)[2], int i)
{
	if (i != 0)
		dup2((*my_pipe)[i - 1][STDIN], STDIN);
	if (cmd[i + 1])
		dup2((*my_pipe)[i][STDOUT], STDOUT);
	close_pipe(cmd, my_pipe);
}
