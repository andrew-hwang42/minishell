/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:47:35 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/02 09:03:34 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "./minishell.h"
# include <stddef.h>

/* parse.c */
t_cmd	**parse(t_cmd **cmd, char **env, char *line);

/* check_parse_err.c */
void	token_err_msg(char c1, char c2);
int		check_quote_pair(char *line);
int		check_parse_err(char *line, t_cmd **cmd);

/* check_token.c */
int		check_token_pipe(char next);
int		check_token_redir(char *line, int i);
int		check_token_else(char curr, char next);
int		check_token(char *line);

/* check_token_pos.c */
int		check_pos_front(char *line, int i, char token);
int		check_pos_back(char *line, int *i, char token);
int		check_pos_err(char *line, int *i);
int		check_token_pos(char *line);

/* apply_env_var.c */
int		double_quote_is_open(int cnt_double_quote);
int		might_be_env_value(char curr, char next);
char	*apply_env_var(char **env, char *line);
char	*make_space_near_redir(char *line);

/* remove_dollar_quote.c */
int		dollar_is_removable(char *line, int i);
void	remove_dollar(char *line);
int		check_echo_replace_token(char *line, int quote_start, int quote_end);
int		check_echo_replace_quote(char *line, int i);
void	remove_quote(char *line);

/* replace_env_key_to_val.c */
char	*fill_line(char *line, char *value, char *front, char *back);
char	*replace_key_to_value(char **line,
			char *key, char *value, int *pos_key_start);
char	*check_env_value(char **env, char *line,
			int *pos_key_start, int pos_key_end);
char	*replace_env_key_to_val(char **env, char *line, int *i);

/* save_data.c */
t_cmd	**realloc_cmd(t_cmd **cmd, int i);
void	revert_echo_option(char *option_i);
t_cmd	**save_data(t_cmd **cmd, char *cmd_splitted_pipe, int i);

/* save_option.c */
int		is_redir(char *str);
char	**save_option(char **option, int cnt_option);

/* save_redir.c */
int		count_redir(char **option);
t_redir	**alloc_redir(int cnt);
void	fill_redir(t_redir **res, char **option);
t_redir	**save_redir(char **option);

/* parse_utils.c */
void	*ft_realloc(void *old_ptr, size_t old_len, size_t new_len);
int		find_char_pos(char *str, char c, int start);
char	*remove_str_from_line(char *line, int str_start_pos, int str_len);

#endif
