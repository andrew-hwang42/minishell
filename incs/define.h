/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:44:27 by ahwang            #+#    #+#             */
/*   Updated: 2025/12/02 08:42:01 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define BLACK			"\x1b[0m"
# define RED			"\x1b[31m"
# define CYAN			"\x1b[36m"
# define YELLOW			"\x1b[33m"

# define STDIN			0
# define STDOUT			1
# define STDERR			2

# define DOUBLE_QUOTE		11
# define SINGLE_QUOTE		12
# define SPACE_IN_QUOTE		13
# define REDIR_IN_QUOTE_IN	14
# define REDIR_IN_QUOTE_OUT	15
# define PIPE_IN_QUOTE		16

# define FD_IN			0
# define FD_OUT			1

# define NONE			1
# define IN			2
# define OUT			3
# define HEREDOC		4
# define APPEND			5

# define CHILD			0
# define PARENTS		1

#endif
