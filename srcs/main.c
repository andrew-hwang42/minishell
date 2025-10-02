/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 00:49:36 by ahwang            #+#    #+#             */
/*   Updated: 2025/10/02 07:17:11 by ahwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	g_exit;

void	show_header(void)
{
	printf("%s\n", CYAN);
	printf("╔════╦════╦══╦════════╦══╦═══════╦══╗  ╔══╦═══════╦══╗  ╔══╗   \n");
	printf("║🫧  ║🐡  ║🫧║ 🐠     ║  ║🪼     ║🫧║  ║  ║     🐋║🐳║  ║🐬║   \n");
	printf("║ 🐬 ║    ║  ║  ╔══╗  ║🦑║   ════╣🦀╚══╝  ║   ════╣  ║  ║  ║🫧 \n");
	printf("║  ║ ║ ║  ║  ║  ║  ║  ║  ║🫧🐡   ║      🐟║     🫧║🐠║  ║  ║🫧 \n");
	printf("║  ║ ║ ║  ║  ║  ║  ║🐚║  ╠════   ║  ╔══╗  ║   ════╣  ╚══╣  ╚══╗\n");
	printf("║🐡║   ║🦑║🐙║  ║  ║🪸║  ║    🦐 ║  ║  ║🐙║🐠   🪸║   🦞║🐚   ║\n");
	printf("╚══╩═══╩══╩══╩══╝  ╚══╩══╩═══════╩══╝  ╚══╩═══════╩═════╩═════╝\n");
	printf("                                                               \n");
	printf("%s\n", BLACK);
}

/* erase later */
void	print_cmd(t_cmd **cmd)
{
	int	i;
	int	j;

	i = -1;
	while (cmd[++i])
	{
		printf("cmd[%d]->cmd: %s\n", i, cmd[i]->cmd);
		j = -1;
		while (cmd[i]->option[++j])
			printf("cmd[%d]->option[%d]: %s\n", i, j, cmd[i]->option[j]);
		j = -1;
		while (cmd[i]->redir[++j])
		{
			printf("cmd[%d]->redir[%d]->redir_type: ", i, j);
			if (cmd[i]->redir[j]->redir_type == HEREDOC)
				printf("<<\n");
			else if (cmd[i]->redir[j]->redir_type == IN)
				printf("<\n");
			else if (cmd[i]->redir[j]->redir_type == OUT)
				printf(">\n");
			else if (cmd[i]->redir[j]->redir_type == APPEND)
				printf(">>\n");
			else if (cmd[i]->redir[j]->redir_type == NONE)
				printf("NONE\n");
			else
				printf("something is wrong\n");
			printf("cmd[%d]->redir[%d]->file: %s\n", i, j, cmd[i]->redir[j]->file);
		}
		printf("cmd[%d]->exit: %d\n", i, cmd[i]->exit);
		printf("cmd[%d]->pid: %d\n", i, cmd[i]->pid);
		printf("------------------------------------\n");
	}
}

int	minishell_main(t_cmd **cmd, char **env)
{
	char	*line;

	while (1)
	{
		detect_signal();
		cmd = ft_calloc(sizeof(t_cmd *), 2);
		if (!cmd)
			return (exit_program(NULL, env, "malloc error"), 0);
		line = readline("\001\x1b[36m\002minishell$\001\x1b[0m\002 ");
		if (!line)
		{
			printf("exit\n");
			return (exit_program(cmd, env, NULL), 0);
		}
		add_history(line);
		cmd = parse(cmd, env, line);
		if (!cmd)
			continue ;
		// print_cmd(cmd); //erase later
		if (execute(cmd, env))
			return (exit_program(cmd, env, NULL), 0);
		free_cmd(cmd);
	}
	return (free_2d_arr(env), 1);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	**cmd;

	(void)argv;
	if (argc != 1)
	{
		err_msg("Argument error");
		return (1);
	}
	if (!set_env(&env) || env == NULL)
		return (1);
	show_header();
	cmd = NULL;
	if (!minishell_main(cmd, env))
		return (1);
	return (0);
}
