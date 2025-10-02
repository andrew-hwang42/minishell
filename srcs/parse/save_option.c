/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 03:27:33 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/02 06:50:46 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	is_redir(char *str)
{
	if (is_same_str("<", str)
		|| is_same_str("<<", str)
		|| is_same_str(">", str)
		|| is_same_str(">>", str))
		return (1);
	return (0);
}

char	**save_option(char **option, int cnt_option)
{
	char	**res;
	int		i;
	int		j;

	res = ft_calloc(sizeof(char *), cnt_option + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (option[i])
	{
		if (is_redir(option[i]))
		{
			i = i + 2;
			continue ;
		}
		res[j] = ft_strdup(option[i]);
		j++;
		i++;
	}
	return (res);
}
