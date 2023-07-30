/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:44:07 by junggkim          #+#    #+#             */
/*   Updated: 2023/07/26 08:59:22 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <termios.h>
#include "minishell.h"

void ft_handler(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다?
		exit(1);
	rl_replace_line("", 0); // 프롬프트에 이미 친 문자열을 싹 날려준다.
	rl_redisplay();			// 프롬프트 커서가 움직이지 않게 해준다.
}

void signal_setting()
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
}

int ft_whitespace(char *line)
{
	while (*line)
	{
		if (!(*line >= 9 && *line <= 13) && *line != 32)
			return (0);
		line++;
	}
	return (1);
}

void init(int argc, char *argv[], t_info *info, t_env *change_env)
{
	struct termios termios_new;

	(void)argc;
	(void)argv;
	if (argc != 1)
	{
		printf("argument error!!\n");
		exit(1);
	}
	change_env->question_mark = 0;
	info->pipe_flag = 1;
	info->start = 0;
	info->quote_flag = 0;
	tcgetattr(STDIN_FILENO, &termios_new);
	termios_new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
}


char **copy_envp(char **envp)
{
	char **tmp;
	int i;

	i = 0;
	while (envp[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	while (envp[++i])
		tmp[i] = ft_strdup(envp[i]);
	tmp[i] = NULL;
	return (tmp);
}

int main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*list;
	t_env			*head;
	struct termios	termios_old;
	char			**tmp_envp;
	t_info			*info;

	tcgetattr(STDIN_FILENO, &termios_old);
	init(argc, argv, info, change_env); //change_env == head
	tmp_envp = copy_envp(envp);
	signal_setting();
	head = find_env(envp);
	while (1)
	{
		line = readline("minishell $ ");
		if (!line) // EOF 처리 : ctr + d
			break;
		if (*line != '\0')
			add_history(line);
		/* 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 */
		if (*line != '\0' && !ft_whitespace(line)) // 프롬프트상에서 입력된 문자가 null || 모두 white_space일 
		{
			parsing(list, line, tmp_envp, info);
			execute(list, head);
		}
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_old);
	// TSCANOW : 속성을 바로 변경한다
}