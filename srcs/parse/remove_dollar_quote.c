/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dollar_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:13:47 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/02 08:59:31 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	dollar_is_removable(char *line, int i)
{
	if (line[i + 1] && (line[i + 1] == '\'' || line[i + 1] == '"'))
		return (1);
	return (0);
}

void	remove_dollar(char *line)
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
		if (line[i] == '$')
		{
			if (dollar_is_removable(line, i))
			{
				line = remove_str_from_line(line, i, ft_strlen("$"));
				i--;
			}
		}
		i++;
	}
}

int	check_echo_replace_token(char *line, int quote_start, int quote_end)
{
	int	i;

	i = quote_start + 1;
	while (i < quote_end)
	{
		if (line[i] == ' ')
			line[i] = SPACE_IN_QUOTE;
		if (line[i] == '<')
			line[i] = REDIR_IN_QUOTE_IN;
		if (line[i] == '>')
			line[i] = REDIR_IN_QUOTE_OUT;
		if (line[i] == '|')
			line[i] = PIPE_IN_QUOTE;
		i++;
	}
	return (1);
}

int	check_echo_replace_quote(char *line, int i)
{
	int		i_cpy;
	int		quote_end;
	char	replaced_quote;

	i_cpy = i;
	i--;
	while (line[i] == ' ')
		i--;
	while (line[i] == 'n')
		i--;
	if (line[i] == '-')
		i--;
	while (line[i] == ' ')
		i--;
	if (i >= 3 && !ft_strncmp(&line[i - 3], "echo", 4))
	{
		quote_end = find_char_pos(line, line[i_cpy], i_cpy + 1);
		replaced_quote = DOUBLE_QUOTE;
		if (line[i_cpy] == '\'')
			replaced_quote = SINGLE_QUOTE;
		line[i_cpy] = replaced_quote;
		line[quote_end] = replaced_quote;
		return (check_echo_replace_token(line, i_cpy, quote_end));
	}
	return (0);
}

void	remove_quote(char *line)
{
	int	quote_end;
	int	i;

	if (!line)
		return ;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			if (check_echo_replace_quote(line, i))
			{
				i = find_char_pos(line, line[i], i + 1) + 1;
				continue ;
			}
			quote_end = find_char_pos(line, line[i], i + 1);
			line = remove_str_from_line(line, quote_end, 1);
			line = remove_str_from_line(line, i, 1);
			i = quote_end - 2;
		}
		i++;
	}
}
