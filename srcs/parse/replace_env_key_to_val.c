/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_key_to_val.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:15:47 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 22:05:10 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*fill_line(char *line, char *value, char *front, char *back)
{
	int	i;
	int	j;

	i = -1;
	while (front[++i])
		line[i] = front[i];
	j = -1;
	while (value[++j])
		line[i++] = value[j];
	j = -1;
	while (back[++j])
		line[i++] = back[j];
	free(front);
	free(back);
	free(value);
	return (line);
}

char	*replace_key_to_value(char **line,
				char *key, char *value, int *pos_key_start)
{
	char	*new_line;
	char	*front;
	char	*back;

	front = ft_substr(*line, 0, *pos_key_start);
	back = ft_substr(*line, *pos_key_start + ft_strlen(key),
			ft_strlen(*line) - ft_strlen(front));
	free(key);
	new_line = ft_calloc(sizeof(char),
			ft_strlen(front) + ft_strlen(value) + ft_strlen(back) + 1);
	if (!new_line)
	{
		free(value);
		free(front);
		free(back);
		free(*line);
		return (err_msg("malloc error"), NULL);
	}
	*pos_key_start = *pos_key_start + ft_strlen(value) - 1;
	free(*line);
	*line = fill_line(new_line, value, front, back);
	return (*line);
}

char	*check_env_value(char **env, char *line,
				int *pos_key_start, int pos_key_end)
{
	char	*key;
	char	*value;
	int		i;

	key = ft_substr(line, *pos_key_start, pos_key_end - *pos_key_start + 1);
	value = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0
			&& env[i][ft_strlen(key)] == '=')
		{
			value = ft_strdup(env[i]);
			value = remove_str_from_line(value, 0, ft_strlen(key) + 1);
		}
		i++;
	}
	if (!value)
		value = ft_strdup("");
	return (replace_key_to_value(&line, key, value, pos_key_start));
}

char	*replace_env_key_to_val(char **env, char *line, int *i)
{
	int	pos_key_end;

	line = remove_str_from_line(line, *i, ft_strlen("$"));
	if (line[*i] == '?')
		return (replace_key_to_value(&line,
				ft_strdup("?"), ft_itoa(g_exit), i));
	pos_key_end = *i + 1;
	while (line[pos_key_end]
		&& line[pos_key_end] != ' ' && line[pos_key_end] != '$'
		&& line[pos_key_end] != '\'' && line[pos_key_end] != '"')
		pos_key_end++;
	pos_key_end--;
	return (check_env_value(env, line, i, pos_key_end));
}
