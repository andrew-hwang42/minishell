/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 05:23:58 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 20:35:56 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	check_pos_err(char *line, int *i)
{
	char	token;
	char	token_next;

	token = line[*i];
	line++;
	token_next = 0;
	if ((line[*i] == '>' || line[*i] == '<') && line[*i] == token)
	{
		token_next = line[*i];
		(*i)++;
	}
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] == '\0'
		|| line[*i] == '|' || line[*i] == '>' || line[*i] == '<')
		return (token_err_msg(token, token_next), 0);
	return (1);
}

int	check_token_pos(char *line)
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
		if ((line[i] == '|' || line[i] == '>' || line[i] == '<')
			&& !check_pos_err(line, &i))
			return (0);
		i++;
	}
	return (1);
}
