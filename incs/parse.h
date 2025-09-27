/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:47:35 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 06:16:42 by ahwang           ###   ########.fr       */
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
int	check_parse_err(char *line, t_cmd **cmd);

/* check_token.c */
int		check_token_quote(char *line);
int		check_token_pipe(char next);
int		check_token_redir(char *line, int i);
int		check_token_else(char curr, char next);
int		check_token(char *line);

/* check_pos.c */
int		check_pos(char *line);

/* parse_utils.c */
void	*ft_realloc(void *old_ptr, size_t old_len, size_t new_len);
int		find_char_pos(char *str, char c, int start);

#endif
