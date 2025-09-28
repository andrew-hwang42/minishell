/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 03:43:20 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 16:01:09 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	token_err_msg(char c1, char c2)
{
	ft_putstr_fd(RED, STDERR);
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR);
	ft_putchar_fd(c1, STDERR);
	if (c2)
		ft_putchar_fd(c2, STDERR);
	ft_putstr_fd("\'\n", STDERR);
	ft_putstr_fd(BLACK, STDERR);
}

int	check_quote_pair(char *line)
{
	char	quote;
	int		i;
	int		pos;

	i = 0;
	pos = 0;
	while (line[i] != '\0' && pos >= 0)
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i++;
			pos = find_char_pos(line, quote, i);
			i = (pos + 1);
			continue ;
		}
		i++;
	}
	if (pos == -1)
		return (token_err_msg(quote, 0), 0);
	return (1);
}

int	check_parse_err(char *line, t_cmd **cmd)
{
	if (!check_quote_pair(line) || !check_token(line)
		|| !check_token_pos(line))
	{
		g_exit = 2;
		return (free_cmd(cmd), 0);
	}
	return (1);
}
