/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 03:28:59 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/02 08:59:19 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	count_redir(char **option)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (option[i])
	{
		if (is_redir(option[i]))
			cnt++;
		i++;
	}
	return (cnt);
}

t_redir	**alloc_redir(int cnt)
{
	t_redir	**res;
	int		i;

	if (!cnt)
		cnt++;
	res = ft_calloc(sizeof(t_redir **), cnt + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < cnt)
	{
		res[i] = ft_calloc(sizeof(t_redir *), 2);
		if (!res[i])
			return (NULL);
		i++;
	}
	return (res);
}

void	fill_redir(t_redir **res, char **option)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (res[++i])
	{
		while (!is_redir(option[j]))
			j++;
		if (option[j][0] == '<')
		{
			res[i]->redir_type = IN;
			if (ft_strlen(option[j]) == 2)
				res[i]->redir_type = HEREDOC;
		}
		else
		{
			res[i]->redir_type = OUT;
			if (ft_strlen(option[j]) == 2)
				res[i]->redir_type = APPEND;
		}
		res[i]->file = ft_strdup(option[++j]);
		j++;
	}
}

t_redir	**save_redir(char **option)
{
	t_redir	**res;
	int		cnt;

	cnt = count_redir(option);
	res = alloc_redir(cnt);
	if (!res)
		return (NULL);
	if (cnt == 0)
	{
		res[0]->redir_type = NONE;
		return (res);
	}
	fill_redir(res, option);
	return (res);
}
