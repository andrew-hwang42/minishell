/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:18:33 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 12:17:43 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**remove_from_env(char **env, char *to_remove)
{
	char	**new_env;
	int		cnt;
	int		i;
	int		j;

	cnt = 0;
	i = -1;
	while (env[++i])
	{
		if ((!ft_strncmp(env[i], to_remove, ft_strlen(to_remove))
				&& env[i][ft_strlen(to_remove)] == '='))
			cnt++;
	}
	if (!cnt)
		return (env);
	new_env = (char **)ft_calloc(sizeof(char *), i);
	i = -1;
	j = 0;
	while (env[++i])
	{
		if (!(!ft_strncmp(env[i], to_remove, ft_strlen(to_remove))
				&& env[i][ft_strlen(to_remove)] == '='))
			new_env[j++] = ft_strdup(env[i]);
	}
	return (free_2d_arr(env), new_env);
}

int	set_env(char ***env)
{
	char	**new_env;
	int		i;

	new_env = (char **)ft_calloc(sizeof(char *), 2);
	if (!new_env)
		return (err_msg("malloc error"), 0);
	i = -1;
	while ((*env)[++i] && find_char_pos((*env)[i], '=', 0) != -1)
	{
		if (i > 0)
			new_env = ft_realloc(new_env, sizeof(char *) * (i + 1),
					sizeof(char *) * (i + 2));
		new_env[i] = ft_strdup((*env)[i]);
		if (!new_env[i])
		{
			free_2d_arr(new_env);
			return (err_msg("malloc error"), 0);
		}
	}
	new_env = remove_from_env(new_env, "OLDPWD");
	*env = new_env;
	return (1);
}
