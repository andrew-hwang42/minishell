/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:43:45 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/02 06:47:40 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./define.h"
# include "./struct.h"
# include "./parse.h"
# include "./execute.h"
# include "../libft/incs/libft.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <asm/ioctl.h>

/* global variable */
extern int	g_exit;

/* main.c */
void	show_header(void);
int		minishell_main(t_cmd **cmd, char **env);
int		main(int argc, char **argv, char **env);

/* set_env.c */
char	**remove_from_env(char **env, char *to_remove);
int		set_env(char ***env);

/* detect_signal.c */
void	handle_sigint(int pid);
void	handle_sigquit(int pid);
void	signal_handler(int signo);
void	detect_signal(void);

/* utils.c */
void	err_msg(char *msg);
int		is_same_str(char *s1, char *s2);
void	free_2d_arr(char **arr);
void	free_cmd(t_cmd **cmd);
void	exit_program(t_cmd **cmd, char **env, char *msg);

#endif
