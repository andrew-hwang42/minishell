/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 06:42:04 by ahwang            #+#    #+#             */
/*   Updated: 2025/03/11 23:05:40 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	find_newline(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*check_save(char *save)
{
	if (!save)
	{
		save = (char *)malloc(sizeof(char));
		if (!save)
			return (0);
		save[0] = '\0';
	}
	return (save);
}

char	*merge(char *save, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	save = check_save(save);
	new_str = malloc(sizeof(char)
			* (ft_strlen(save) + ft_strlen(buffer) + 1));
	if (!new_str || !buffer)
		return (NULL);
	i = 0;
	j = 0;
	if (save)
	{
		while (save[i] != '\0')
		{
			new_str[i] = save[i];
			i++;
		}
	}
	while (buffer[j] != '\0')
		new_str[i++] = buffer[j++];
	new_str[ft_strlen(save) + ft_strlen(buffer)] = '\0';
	free(save);
	return (new_str);
}
