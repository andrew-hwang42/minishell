/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 05:28:44 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/04 02:57:02 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	handle_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		ioctl(STDIN, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit = 130;
	}
}

char	*generate_file_name(int i, int j)
{
	char	*nb;
	char	*tmp;

	nb = ft_itoa(i * 10 + j);
	tmp = ft_strjoin("/tmp/.heredoc_", nb);
	free(nb);
	return (tmp);
}

void	err_msg_heredoc(char *delim)
{
	ft_putstr_fd("minishell: warning: here document ", STDERR);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR);
	ft_putstr_fd(delim, STDERR);
	ft_putstr_fd("')\n", STDERR);
}

int	write_heredoc(char *file_name, char *delim)
{
	char	*line;
	int		fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
		return (err_msg("file open error"), 0);
	g_exit = 0;
	while (g_exit != 130)
	{
		signal(SIGINT, handle_heredoc);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (!line)
			return (err_msg_heredoc(delim), close(fd), 1);
		if (is_same_str(line, delim))
			return (free(line), close(fd), 1);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (g_exit == 130)
		return (close(fd), 1);
	return (close(fd), 1);
}

int	check_heredoc(t_cmd **cmd)
{
	char	*file_name;
	int		i;
	int		j;

	i = -1;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i]->redir[++j])
		{
			if (cmd[i]->redir[j]->redir_type == HEREDOC)
			{
				file_name = generate_file_name(i, j);
				if (!write_heredoc(file_name, cmd[i]->redir[j]->file))
					return (free(file_name), 0);
				free(cmd[i]->redir[j]->file);
				cmd[i]->redir[j]->file = file_name;
			}
		}
	}
	return (1);
}
