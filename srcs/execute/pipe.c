/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 04:17:57 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/02 08:37:29 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	create_pipe(t_cmd **cmd, int (**my_pipe)[2])
{
	int	i;

	i = 0;
	*my_pipe = NULL;
	while (cmd[i + 1])
	{
		*my_pipe = ft_realloc(*my_pipe,
				sizeof(**my_pipe) * i, sizeof(**my_pipe) * (i + 1));
		if (!*my_pipe)
			return (err_msg("malloc error"), 0);
		if (pipe((*my_pipe)[i]) == -1)
			return (err_msg("pipe error"), 0);
		i++;
	}
	return (1);
}

void	close_pipe(t_cmd **cmd, int (**my_pipe)[2])
{
	int	i;

	i = 0;
	while (cmd[i + 1])
	{
		close((*my_pipe)[i][STDIN]);
		close((*my_pipe)[i][STDOUT]);
		i++;
	}
}

/*
이전 파이프가 있다면 (i != 0) 내 표준 입력을 이전 명령의 출력 파이프와 연결
다음 파이프가 있다면 (cmd[i + 1]) 내 표준 출력을 다음 명령이 읽을 파이프와 연결
dup2로 필요한 것만 복제했으니, 나머지 파이프 fd는 닫아줘야 함
*/
void	handle_pipe(t_cmd **cmd, int (**my_pipe)[2], int i)
{
	if (i != 0)
		dup2((*my_pipe)[i - 1][STDIN], STDIN);
	if (cmd[i + 1])
		dup2((*my_pipe)[i][STDOUT], STDOUT);
	close_pipe(cmd, my_pipe);
}
