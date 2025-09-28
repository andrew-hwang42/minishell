/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:00:57 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 22:08:19 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	double_quote_is_open(int cnt_double_quote)
{
	if (cnt_double_quote % 2 == 1)
		return (1);
	return (0);
}

int	might_be_env_value(char curr, char next)
{
	if (curr == '$'
		&& (next && next != ' ' && next != '\'' && next != '"'))
		return (1);
	return (0);
}

char	*apply_env_var(char **env, char *line)
{
	char	*new_line;
	int		double_quote;
	int		i;

	new_line = ft_strdup(line);
	if (!new_line)
		return (err_msg("malloc error"), NULL);
	remove_dollar(new_line);
	double_quote = 0;
	i = -1;
	while (new_line != NULL && new_line[++i] != '\0')
	{
		if (new_line[i] == '"')
			double_quote++;
		if (new_line[i] == '\'' && !double_quote_is_open(double_quote))
		{
			i = find_char_pos(new_line, '\'', i + 1);
			continue ;
		}
		if ((!double_quote || double_quote_is_open(double_quote))
			&& might_be_env_value(new_line[i], new_line[i + 1]))
			new_line = replace_env_key_to_val(env, new_line, &i);
	}
	remove_quote(new_line);
	return (new_line);
}

char	*make_space_near_redir(char *line)
{
	int	i;

	if (!line)
		return (NULL);
	i = 0;
	while (line != NULL && line[i] != '\0')
	{
		if (line[i] == '<' && line[i + 1] != '<')
			line = replace_key_to_value(&line,
					ft_strdup("<"), ft_strdup(" < "), &i);
		else if (line[i] == '<' && line[i + 1] == '<')
			line = replace_key_to_value(&line,
					ft_strdup("<<"), ft_strdup(" << "), &i);
		else if (line[i] == '>' && line[i + 1] != '>')
			line = replace_key_to_value(&line,
					ft_strdup(">"), ft_strdup(" > "), &i);
		else if (line[i] == '>' && line[i + 1] == '>')
			line = replace_key_to_value(&line,
					ft_strdup(">>"), ft_strdup(" >> "), &i);
		i++;
	}
	return (line);
}
