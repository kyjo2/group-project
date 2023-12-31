/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:27:14 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/26 00:36:51 by yul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int signal)
{
	g_exit_code = 1;
	if (signal == SIGINT)
		printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	//rl_replace_line("", 1);
	rl_redisplay();
}

void	signal_setting(void)
{
	struct termios	termios_new;

	tcgetattr(STDIN_FILENO, &termios_new);
	termios_new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init(int argc, char *argv[], char **envp, t_info *info)
{
	(void)argv;
	if (argc != 1)
	{
		printf("argument error!!\n");
		exit(1);
	}
	info->envp = envp;
	info->envp_head = find_env(envp);
	g_exit_code = 0;
	info->pipe_flag = 1;
	info->start = 0;
	info->quote_flag = 0;
	info->doubleq_flag = 0;
	info->singleq_flag = 0;
	info->count_doubleq = 0;
	info->count_singleq = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_list			*list;
	t_info			info;
	struct termios	termios_old;
	char			*line;
	
	tcgetattr(STDIN_FILENO, &termios_old);
	line = NULL;
	init(argc, argv, envp, &info);
	while (1)
	{
		signal_setting();
		line = readline("minishell $ ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			parsing(&list, &line, &info);
			execute(list, &info);
		}
		free(line);
	}
	free_env(info.envp_head);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_old);
}
