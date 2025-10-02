/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 05:28:44 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/02 10:00:29 by ahwang           ###   ########.fr       */
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

int	write_heredoc(int *fd, char *file_name, char *delim)
{
	char	*line;

	*fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (*fd == -1)
		return (err_msg("file open error"), 0);
	while (1)
	{
		signal(SIGINT, handle_heredoc);
		signal(SIGQUIT, SIG_IGN);
		line = readline("> ");
		if (!line)
			return (err_msg_heredoc(delim), 1);
		if (g_exit == 130)
		{
			close(*fd);
			return (free(line), 0);
		}
		if (is_same_str(line, delim))
			return (free(line), 1);
		write(*fd, line, ft_strlen(line));
		write(*fd, "\n", 1);
		free(line);
	}
	return (1);
}

int	check_heredoc(t_cmd **cmd)
{
	char	*file_name;
	int		fd;
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
				if (!write_heredoc(&fd, file_name, cmd[i]->redir[j]->file))
					return (free(file_name), 0);
				if (fd >= 0)
					close(fd);
				free(cmd[i]->redir[j]->file);
				cmd[i]->redir[j]->file = file_name;
			}
		}
	}
	return (1);
}
