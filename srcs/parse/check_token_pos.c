/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 05:23:58 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 22:57:38 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	check_pos_front(char *line, int i, char token)
{
	int	flag_redir_double;

	flag_redir_double = 0;
	if (line[i + 1] && (line[i + 1] == '<' || line[i + 1] == '>'))
		flag_redir_double = 1;
	if (i == 0)
	{
		if (flag_redir_double)
			return (token_err_msg(token, token), 0);
		return (token_err_msg(token, 0), 0);
	}
	i--;
	while (i > 0 && line[i] == ' ')
		i--;
	if (i == 0 || line[i] == '|'
		|| line[i] == '<' || line[i] == '>')
	{
		if (flag_redir_double)
			return (token_err_msg(token, token), 0);
		return (token_err_msg(token, 0), 0);
	}
	return (1);
}

int	check_pos_back(char *line, int *i, char token)
{
	(*i)++;
	if (line[*i] == token)
	{
		(*i)++;
		if (line[*i] == '\0')
			return (token_err_msg(token, token), 0);
		while (line[*i] == ' ')
			(*i)++;
		if (!line[*i])
			return (token_err_msg(token, token), 0);
		if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
			return (token_err_msg(token, token), 0);
	}
	else
	{
		if (line[*i] == '\0')
			return (token_err_msg(token, 0), 0);
		while (line[*i] == ' ')
			(*i)++;
		if (!line[*i])
			return (token_err_msg(token, 0), 0);
		if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
			return (token_err_msg(token, 0), 0);
	}
	return (1);
}

int	check_pos_err(char *line, int *i)
{
	char	token;

	token = line[*i];
	if (!check_pos_front(line, *i, token)
		|| !check_pos_back(line, i, token))
		return (0);
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
