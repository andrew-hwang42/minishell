/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 04:16:09 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/30 03:34:29 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	check_token_pipe(char next)
{
	if (next != '\0')
	{
		if (next == '|')
			return (token_err_msg('|', '|'), 0);
		if (next == '>' || next == '<')
			return (token_err_msg('|', 0), 0);
	}
	return (1);
}

int	check_token_redir(char *line, int i)
{
	if (line[i + 1] != '\0')
	{
		if (line[i] == line[i + 1])
		{
			if (line[i + 2] != '\0')
			{
				if (line[i + 2] == '|')
					return (token_err_msg('|', 0), 0);
				if (line[i + 2] == '>' || line[i + 2] == '<')
					return (token_err_msg(line[i], line[i]), 0);
			}
		}
		else
		{
			if (line[i + 1] == '<' || line[i + 1] == '>')
				return (token_err_msg(line[i], 0), 0);
			else if (line[i + 1] == '|')
				return (token_err_msg('|', 0), 0);
		}
	}
	return (1);
}

int	check_token_else(char curr, char next)
{
	if (curr == ';' || curr == '\\')
		return (token_err_msg(curr, 0), 0);
	else if (curr == '&')
	{
		if (next && next == '&')
			return (token_err_msg(curr, curr), 0);
		return (token_err_msg(curr, 0), 0);
	}
	return (1);
}

int	check_token(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			i = find_char_pos(line, line[i], i + 1) + 1;
			continue ;
		}
		if ((line[i] == '|' && !check_token_pipe(line[i + 1]))
			|| ((line[i] == '>' || line[i] == '<')
				&& !check_token_redir(line, i))
			|| ((line[i] == ';' || line[i] == '\\' || line[i] == '&')
				&& !check_token_else(line[i], line[i + 1])))
			return (0);
		i++;
	}
	return (1);
}
