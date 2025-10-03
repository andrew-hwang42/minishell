/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:06:10 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/03 02:41:24 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	minishell_err_msg(char *file_name, char *err_msg)
{
	ft_putstr_fd("minishell: ", STDERR);
	if (file_name)
	{
		ft_putstr_fd(file_name, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putstr_fd(err_msg, STDERR);
	ft_putstr_fd("\n", STDERR);
}

int	is_builtin(char *cmd)
{
	if (is_same_str("echo", cmd)
		|| is_same_str("cd", cmd)
		|| is_same_str("pwd", cmd)
		|| is_same_str("export", cmd)
		|| is_same_str("unset", cmd)
		|| is_same_str("env", cmd)
		|| is_same_str("exit", cmd))
		return (1);
	return (0);
}
