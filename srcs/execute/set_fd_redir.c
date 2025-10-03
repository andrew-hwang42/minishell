/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:00:27 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 03:26:33 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	redir_open_file(t_redir *redir, int (*fd)[2])
{
	if (redir->redir_type == IN || redir->redir_type == HEREDOC)
	{
		(*fd)[FD_IN] = open(redir->file, O_RDONLY);
		if ((*fd)[FD_IN] == -1)
			return (minishell_err_msg(redir->file,
					"No such file or directory"), 0);
	}
	else if (redir->redir_type == OUT || redir->redir_type == APPEND)
	{
		if (redir->redir_type == OUT)
			(*fd)[FD_OUT]
				= open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		else if (redir->redir_type == APPEND)
			(*fd)[FD_OUT]
				= open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
		if ((*fd)[FD_OUT] == -1)
			return (minishell_err_msg(redir->file,
					"Permission denied"), 0);
	}
	return (1);
}

int	set_fd_redir(t_cmd *cmd)
{
	int	fd[2];
	int	i;

	i = -1;
	while (cmd->redir[++i])
	{
		if (!redir_open_file(cmd->redir[i], &fd))
			return (0);
		if (cmd->redir[i]->redir_type == IN
			|| cmd->redir[i]->redir_type == HEREDOC)
		{
			dup2(fd[FD_IN], STDIN);
			close(fd[FD_IN]);
			if (cmd->redir[i]->redir_type == HEREDOC)
				unlink(cmd->redir[i]->file);
		}
		else if (cmd->redir[i]->redir_type == OUT
			|| cmd->redir[i]->redir_type == APPEND)
		{
			dup2(fd[FD_OUT], STDOUT);
			close(fd[FD_OUT]);
		}
	}
	return (1);
}
