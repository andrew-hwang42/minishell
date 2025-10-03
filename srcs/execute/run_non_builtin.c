/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_non_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 03:54:16 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 03:56:38 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*check_valid_path_with_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*path_with_cmd;
	int		i;

	i = -1;
	if (access(cmd, F_OK) == 0)
		return (free_2d_arr(path), cmd);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		path_with_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path_with_cmd, F_OK) == 0)
			return (free_2d_arr(path), path_with_cmd);
		free(path_with_cmd);
	}
	return (free_2d_arr(path), NULL);
}

char	*find_valid_path_with_cmd(t_cmd *cmd, char **env)
{
	char	*path_value;
	char	**path;
	int		i;

	i = -1;
	path_value = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH", ft_strlen("PATH"))
			&& env[i][ft_strlen("PATH")] == '=')
			path_value = ft_strdup(env[i]);
	}
	if (!path_value)
		return (NULL);
	path_value = remove_str_from_line(path_value, 0, ft_strlen("PATH="));
	path = ft_split(path_value, ':');
	free(path_value);
	if (!path)
		return (NULL);
	return (check_valid_path_with_cmd(path, cmd->cmd));
}

void	run_valid_path_with_cmd(t_cmd *cmd, char **env, char *path_with_cmd)
{
	char		**argv;
	struct stat	buf;
	int			i;

	argv = ft_calloc(sizeof(char *), 2);
	argv[0] = ft_strdup(cmd->cmd);
	i = -1;
	while (cmd->option[++i])
	{
		argv = ft_realloc(argv,
				sizeof(char *) * (i + 2), (sizeof(char *) * (i + 3)));
		argv[i + 1] = ft_strdup(cmd->option[i]);
	}
	execve(path_with_cmd, argv, env);
	stat(argv[0], &buf);
	if (S_ISDIR(buf.st_mode))
	{
		minishell_err_msg(NULL, "Is a directory");
		exit(127);
	}
	free(path_with_cmd);
	free_2d_arr(argv);
}

void	run_non_builtin(t_cmd *cmd, char **env)
{
	char	*path_with_cmd;

	path_with_cmd = find_valid_path_with_cmd(cmd, env);
	if (!path_with_cmd)
	{
		if (cmd->cmd[0] == '.' || cmd->cmd[0] == '/')
			minishell_err_msg(NULL, "No such file or directory");
		else
			minishell_err_msg(cmd->cmd, "command not found");
		g_exit = 127;
	}
	else
		run_valid_path_with_cmd(cmd, env, path_with_cmd);
}
