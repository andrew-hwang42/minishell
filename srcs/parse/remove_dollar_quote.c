/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_dollar_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:13:47 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 20:36:13 by ahwang           ###   ########.fr       */
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
			quote_end = find_char_pos(line, line[i], i + 1);
			line = remove_str_from_line(line, quote_end, 1);
			line = remove_str_from_line(line, i, 1);
			i = quote_end - 2;
		}
		i++;
	}
}
