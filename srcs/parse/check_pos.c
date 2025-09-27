/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 05:23:58 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 06:29:14 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	check_pos(char *line)
{
	int	i;
	char	quote;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			quote = line[i];
			i = find_char_pos(line, quote, i + 1) + 1;
			continue ;
		}
		// printf("%c\n", line[i]);
		i++;
	}
	return (1);
}