/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 06:42:09 by ahwang            #+#    #+#             */
/*   Updated: 2025/03/11 23:17:39 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

/* get_next_line.c */
char	*read_line(int fd, char *save);
char	*get_line(char *save);
char	*update_save(char *save);
char	*get_next_line(int fd);

/* get_next_line_utils.c */
size_t	ft_strlen(char *s);
int		find_newline(char *s);
char	*check_save(char *save);
char	*merge(char *save, char *buffer);

#endif
