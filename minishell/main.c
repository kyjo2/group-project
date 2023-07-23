/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:44:07 by junggkim          #+#    #+#             */
/*   Updated: 2023/07/23 13:41:55 by junggkim         ###   ########.fr       */
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

int ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	if (s1 == s2)
		return (0);
	if (s1[0] == '\0' && s2[0] == '\0')
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

void check_command(char *line, char **envp)
{
	if (ft_strcmp(line, "cd"))
		ft_cd(line);
	else if (ft_strcmp(line, "echo"))
		ft_echo(line);
	else if (ft_strcmp(line, "env"))
		ft_env(line);
	else if (ft_strcmp(line, "exit"))
		ft_exit(line);
	else if (ft_strcmp(line, "export"))
		ft_export(line);
	else if (ft_strcmp(line, "pwd"))
		ft_pwd(line);
	else if (ft_strcmp(line, "unset"))
		ft_unset(line);
}

void parcing(t_list *list, char *line, char **envp)
{
	// check 요소 : 파이프라인, 따움표두개, 따움표한개, 쉽표한개,쉼표두개
	int i;

	i = 0;
	while (*line)
	{
	}

	check_command(line, envp);
	int i;
	int start;
	int pipe_flag;
	t_cmd *tmp;
	t_cmd *new;
	int quote_flag;

	quote_flag = 0;
	i = 0;
	start = 0;
	pipe_flag = 1;
	while (1) // readline으로 입력받은 line을 모두 하나하나 체크하는 loop입니다.
	{
		if ((line[i] == '\"' || line[i] == '\'') && quote_flag == 0) // 파이프가 따옴표 안에 들어가는 경우 끊으면 안됨.
			quote_flag = 1;
		else if ((line[i] == '\"' || line[i] == '\'') && quote_flag == 1)
			quote_flag = 0;
		if (line[i] == '\0' || (line[i] == '|' && quote_flag == 0)) // 파이프를 기준으로 명령어를 나누기 위해 설정한 조건문입니다. null을 만날 경우, 이전까지의 명령어를 list의 노드로 생성합니다.
		{
			if (line[i] == '|')
				line[i] = '\0'; // 파이프문자를 null로 바꾸어 split을 용이하게 합니다.
			else
				pipe_flag = 0;
			if ((new = ft_new(&line[start], pipe_flag, envp, start)) == 0)
				return;
			if (start == 0)
			{
				*cmd_list = new;
				tmp = *cmd_list;
			}
			else // 처음 노드가 아니기 때문에 list가 존재하므로 next로 연결해줍니다.
			{
				(*cmd_list)->next = new;
				*cmd_list = (*cmd_list)->next;
			}
			if (pipe_flag == 0) // 마지막 노드이므로 while loop를 벗어납니다.
				break;
			start = i + 1; // split할 명령어의 첫번째 index를 파이프의 다음 index로 갱신시켜줍니다.
		}
		i++;
	}
	*cmd_list = tmp; // backup 해놨던 첫번째 명령어의 주소를 cmd_list에 넣어 반환합니다.
}
}

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

void init(int argc, char *argv[])
{
	struct termios termios_new;

	(void)argc;
	(void)argv;
	if (argc != 1)
	{
		printf("argument error!!\n");
		exit(1);
	}
	tcgetattr(STDIN_FILENO, &termios_new);
	termios_new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
}

typedef struct s_list
{
	void *data;
	struct s_list *next;
} t_list;

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
	char *line;
	t_list *list;
	struct termios termios_old;
	char **tmp_envp;

	tcgetattr(STDIN_FILENO, &termios_old);
	init(argc, argv);
	tmp_envp = copy_envp(envp);
	signal_setting();
	while (1)
	{
		line = readline("minishell $ ");
		if (!line) // EOF 처리 : ctr + d
			break;
		if (*line != '\0')
			add_history(line);
		/* 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 */
		if (*line != '\0' && !ft_whitespace(line)) // 프롬프트상에서 입력된 문자가 null || 모두 white_space일 때		{
		{
			parsing(list, line, tmp_envp);
		}
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_old);
	// TSCANOW : 속성을 바로 변경한다
}