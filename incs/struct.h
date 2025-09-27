/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:45:33 by ahwang            #+#    #+#             */
/*   Updated: 2025/09/27 05:54:17 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./minishell.h"

typedef struct s_redir
{
	int			flag_redir;
	char		*file;
}	t_redir;

typedef struct s_cmd
{
	char		*cmd;
	char		**option;
	t_redir		**redir;
	int			exit;
	int			pid;
}	t_cmd;

#endif
