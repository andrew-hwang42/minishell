/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:47:40 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 09:19:16 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "./minishell.h"

/* execute_main.c */
void		wait_for_child_process(t_cmd **cmd);
void		check_fork_set_fd(t_cmd **cmd, int i, int (*fd)[2]);
void		revert_close_fd(int (*fd)[2]);
int			execute(t_cmd **cmd, char **env, int (**my_pipe)[2], int (*fd)[2]);
int			execute_main(t_cmd **cmd, char **env);

/* check_heredoc.c */
void		handle_heredoc(int signo);
char		*generate_file_name(int i, int j);
void		err_msg_heredoc(char *delim);
int			write_heredoc(char *file_name, char *delim);
int			check_heredoc(t_cmd **cmd);

/* handle_pipe.c */
int			create_pipe(t_cmd **cmd, int (**my_pipe)[2]);
void		close_pipe(t_cmd **cmd, int (**my_pipe)[2]);
void		handle_pipe(t_cmd **cmd, int (**my_pipe)[2], int i);

/* set_fd_redir.c */
int			redir_open_file(t_redir *redir, int (*fd)[2]);
int			set_fd_redir(t_cmd *cmd);

/* run_command.c */
void		check_pid(t_cmd **cmd, char **env, int i, int exit_code);
void		run_command(t_cmd **cmd, char **env, int (*fd)[2], int i);

/* run_builtin.c */
void		run_echo(t_cmd *cmd);
void		run_pwd(t_cmd *cmd);
void		run_unset(t_cmd *cmd, char **env);
void		run_env(t_cmd *cmd, char **env);
int			run_exit(t_cmd *cmd);

/* run_non_builtin.c */
char		*check_valid_path_with_cmd(char **path, char *cmd);
char		*find_valid_path_with_cmd(t_cmd *cmd, char **env);
int			run_valid_path_with_cmd(t_cmd *cmd,
				char **env, char *path_with_cmd);
int			run_non_builtin(t_cmd *cmd, char **env);

/* execute_utils.c */
void		minishell_err_msg(char *file_name, char *err_msg);
int			is_builtin(char *cmd);
long long	ft_atolonglong(char *str);
int			is_numeric_str(char *str);

#endif
