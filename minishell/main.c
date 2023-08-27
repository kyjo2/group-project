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



t_env	*find_env(char **ev)
{
	t_env	*head;
	t_env	*temp;
	t_env	*new;
	char	*str;
	int		i;

	new = malloc(sizeof(t_env));
	new->next = NULL;
	head = new;
	while (*ev)
	{
		str = ft_strdup(*ev);
		i = 0;
		while (str[i] != '=')
			i++;
		new->name = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(new->name, str, i + 1);
		str += (i + 1);
		new->value = ft_strdup(str);
		ev++;
		if (*ev)
		{
			temp = malloc(sizeof(t_env));
			temp->next = NULL;
			new->next = temp;
			new = temp;
		}
	}
	return (head);
}

void ft_handler(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	if (rl_on_new_line() == -1) // readline으로 설정한 문자열을 한 번 출력한다?
		exit(1);
	//rl_replace_line("", 1); // 프롬프트에 이미 친 문자열을 싹 날려준다.
	rl_redisplay();			// 프롬프트 커서가 움직이지 않게 해준다.
}

void signal_setting()
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
}

void init(int argc, char *argv[], t_info *info, t_env *head)
{
	struct termios termios_new;

	(void)argc;
	(void)argv;
	if (argc != 1)
	{
		printf("argument error!!\n");
		exit(1);
	}
	info->question_mark = "0";    //유동적으로 바꿀수 있어야 한다.
	info->envp_head = head;
	info->pipe_flag = 1;
	info->start = 0;
	info->quote_flag = 0;
	info->doubleq_flag = 0;
	info->singleq_flag = 0;
	tcgetattr(STDIN_FILENO, &termios_new);
	termios_new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_new);
}


//메모리 해제 함수
void free_aa(t_list* head) 
{
    t_list* current;
	t_list* temp;
	
	current = head;
    while (current != NULL) 
	{
        temp = current;
        current = current->next;
        free(temp);
    }
}

int main(int argc, char **argv, char **envp)
{
	t_list			*list;
	t_env			*head;
	t_info			info;
	struct termios	termios_old;
	char			*line;
	//t_list			*tmp_list;

	tcgetattr(STDIN_FILENO, &termios_old);
	line = NULL;
	info.envp = envp;
	head = find_env(envp);
	init(argc, argv, &info, head);
	signal_setting();
	while (1)
	{
		line = readline("minishell $ ");
		printf("11111\n");
		if (!line) // EOF 처리 : ctr + d
			break;
		printf("222222\n");
		if (*line != '\0')
			add_history(line);
		/* 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 */
		if (*line != '\0') // 프롬프트상에서 입력된 문자가 null || 모두 white_space일 
		{
			printf("3333333\n");
			parsing(&list, &line, &info);
			printf("4444444\n");
			// printf("%s\n", list->envp[0]);
			// printf("%d\n", list->exist_pipe);
			// printf("%d\n", list->pip[0]);
			// printf("%d\n", list->infile);
			// printf("%d\n", list->outfile);
			// list->envp = envp;
			// tmp_list = list;
			// // list->prev = NULL;
			// // list->infile = -2;
			// // list->outfile = -2;
			// printf("555555555\n");
			// while (tmp_list->next)
			// {
			// 	printf("av = %s\n", tmp_list->av[1]);
			// 	printf("%d\n", tmp_list->ac);
			// 	//printf("tmp_list = %d\n", tmp_list->exist_pipe);
			// 	tmp_list = tmp_list->next;
			// }
			// while (tmp_list->prev)
			// {
			// 	printf("prev");
			// 	tmp_list = tmp_list->prev;
			// }
			execute(list);
			free_aa(list);
			printf("6666666666\n");
		}
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_old);
	// TSCANOW : 속성을 바로 변경한다
}