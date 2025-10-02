/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 21:06:10 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/02 21:06:40 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
