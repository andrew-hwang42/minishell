/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:47:40 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/02 07:16:56 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "./minishell.h"

/* execute_main.c */
void	wait_for_child_process(t_cmd **cmd);
int		execute(t_cmd **cmd, char **env);

/* heredoc.c */
void	handle_heredoc(int signo);
char	*generate_file_name(int i, int j);
void	write_heredoc(int fd, char *delim);
int		check_heredoc(t_cmd **cmd);

/* pipe.c */
int		create_pipe(t_cmd **cmd, int (**my_pipe)[2]);
void	handle_pipe(t_cmd **cmd, int (**my_pipe)[2], int i);
void	close_pipe(t_cmd **cmd, int (**my_pipe)[2]);

#endif
