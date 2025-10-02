/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 03:50:18 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/02 09:28:57 by ahwang           ###   ########.fr       */
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

/*
부모 프로세스가 여러 개의 자식 프로세스(cmd 배열 안에 있음)를 순서대로 대기,
마지막 프로세스의 종료 코드를 전역 변수 g_exit에 저장
*/
void	wait_for_child_process(t_cmd **cmd)
{
	int	i;
	int	last;
	int	status;

	last = 0;
	while (cmd[last])
		last++;
	last--;
	i = -1;
	/* 마지막 전까지: 자식이 있는 엔트리만 대기 */
	while (++i < last)
	{
		if (cmd[i]->pid > 0) //자식 PID를 보유한 부모: 자식 대기
			waitpid(cmd[i]->pid, NULL, 0);
	}
	/* 마지막 */
	if (cmd[last]->pid > 0) //자식 PID를 보유한 부모: 자식 대기 -> 마지막으로 실행된 프로세스가 자식: non built-in, cmd 여러개 pipe로 연결
	{
		waitpid(cmd[last]->pid, &status, 0);
		if (WIFEXITED(status))
		{
			g_exit = WEXITSTATUS(status);
			if (!g_exit)
				g_exit = cmd[last]->exit;
		}
		else if (WIFSIGNALED(status))
			g_exit = 128 + WTERMSIG(status);
	}
	else //자식이 없는 부모-> 마지막으로 실행된 프로세스가 부모: built-in
		g_exit = cmd[last]->exit;
}

void	redir_err_msg(char *file_name, char *err_msg)
{
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(file_name, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(err_msg, STDERR);
	ft_putstr_fd("\n", STDERR);
}

int	redir_open_file(int *cmd_exit, t_redir *redir, int (*fd)[2])
{
	if (redir->redir_type == IN || redir->redir_type == HEREDOC)
	{
		(*fd)[FD_IN] = open(redir->file, O_RDONLY);
		if ((*fd)[FD_IN] == -1)
		{
			redir_err_msg(redir->file, "No such file or directory");
			return (0);
		}
		
	}
	else
	{
		if (redir->redir_type == OUT)
			(*fd)[FD_OUT]
				= open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		else if (redir->redir_type == APPEND)
			(*fd)[FD_OUT]
				= open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0664);
		if ((*fd)[FD_OUT] == -1)
		{
			redir_err_msg(redir->file, "Permission denied");
			return (0);
		}
	}
	return (1);
}

int	set_fd_redir(t_cmd *cmd)
{
	int	fd[2];
	int	i;

	i = -1;
	while (cmd->redir[++i])
	{
		if (!redir_open_file(&cmd->exit, cmd->redir[i], &fd))
			return (0);
		if (cmd->redir[i]->redir_type == IN
			|| cmd->redir[i]->redir_type == HEREDOC)
		{
			dup2(fd[FD_IN], STDIN);
			close(fd[FD_IN]);
			if (cmd->redir[i]->redir_type == HEREDOC)
				unlink(cmd->redir[i]->file);
		}
		else if (cmd->redir[i]->redir_type == OUT
			|| cmd->redir[i]->redir_type == APPEND)
		{
			dup2(fd[FD_OUT], STDOUT);
			close(fd[FD_OUT]);
		}
	}
	return (1);
}

/*
파싱 후 cmd[i]->pid, cmd[i]->exit 모두 0으로 저장.

heredoc 관련 처리, 있으면 함수 종료
while{ 빌트인 아닌 경우 → 자식 fork
	빌트인 + 파이프라인 포함 → 자식 fork
	빌트인 + 단일 명령어 → 부모에서 실행 }
실행 전 프로세스마다 부모, 자식 적절히 파이프 입출력, fd 세팅
실행 후 자식은 종료 & exit code 회수 (wait_for_child_process)
-자식이 있으면 자식에서 실행 후 종료(부모는 기다리기)
-자식이 없으면 부모에서 실행

<명령어 실행 시 fd, 파이프 핸들링>
-dup으로 원본 fd 백업(원래 표준 입출력을 저장, 명령 실행 끝난 뒤에 항상 되돌릴 수 있음)
-handle_pipe로 파이프 연결
	1. 첫 명령어라면 이전 입력 없음 → 그대로 STDIN 사용
	2. 중간 명령어라면 이전 파이프 출력이 STDIN 연결
	3. 다음 명령어가 있다면 현재 STDOUT을 파이프 출력으로 연결
-HEREDOC을 제외한 리다이렉션 발견 시 fd 핸들링
-명령 하나 끝나면 dup2로 원래 fd 상태 복원 + close
*/
int	execute(t_cmd **cmd, char **env)
{
	int	(*my_pipe)[2];
	int	fd[2];
	int	i;

	if (!check_heredoc(cmd))
		return (0);
	my_pipe = NULL;
	if (create_pipe(cmd, &my_pipe))
		return (0);
	i = -1;
	while (cmd[++i])
	{
		if (!is_builtin(cmd[i]->cmd) || cmd[i + 1] || i > 0)
			cmd[i]->pid = fork();
		else
			cmd[i]->pid = PARENTS;
		if (cmd[i]->pid == CHILD || cmd[i]->pid == PARENTS)
		{
			fd[STDIN] = dup(STDIN);
			fd[STDOUT] = dup(STDOUT);
			handle_pipe(cmd, &my_pipe, i);
			if (!set_fd_redir(cmd[i]))
			{
				dup2(fd[STDIN], STDIN);
				dup2(fd[STDOUT], STDOUT);
				close(fd[STDIN]);
				close(fd[STDOUT]);
				if (cmd[i]->pid == CHILD)
					exit(1);
				g_exit = 1;
				return (0);
			}
			// run_command();
			if (cmd[i]->pid == CHILD)
				exit(cmd[i]->exit);
			dup2(fd[STDIN], STDIN);
			dup2(fd[STDOUT], STDOUT);
			close(fd[STDIN]);
			close(fd[STDOUT]);
		}
	}
	close_pipe(cmd, &my_pipe);
	free(*my_pipe);
	wait_for_child_process(cmd);
	return (1);
}
