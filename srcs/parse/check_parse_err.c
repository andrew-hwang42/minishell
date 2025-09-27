/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 03:43:20 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 06:27:18 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	token_err_msg(char c1, char c2)
{
	ft_putstr_fd(RED, STDERR);
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR);
	ft_putstr_fd(&c1, STDERR);
	if (c2)
		ft_putstr_fd(&c2, STDERR);
	err_msg("'\n");
}

int	check_parse_err(char *line, t_cmd **cmd)
{
	if (!check_token_quote(line) || !check_token(line) || !check_pos(line))
	{
		g_exit = 2;
		return (free_cmd(cmd), 0);
	}
	return (1);
}
