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
		new->have_equl = 1;    //export할떄 필요함
		ev++;
		if (*ev)
		{
			temp = malloc(sizeof(t_env));
			temp->next = NULL;
			new->next = temp;
			new = temp;
		}
		str -= (i + 1);
		free(str);
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
	//t_env *tmp;

	(void)argv;
	if (argc != 1)
	{
		printf("argument error!!\n");
		exit(1);
	}
	info->question_mark = "0";    //유동적으로 바꿀수 있어야 한다.
	info->envp_head = head;
	// tmp = info ->envp_head;
	// while (tmp->next)
	// {
	// 	printf("name = %s value = %s\n", tmp->name, tmp->value);
	// 	tmp = tmp->next;
	// }
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
		if (!line) // EOF 처리 : ctr + d
			break;
		if (*line != '\0')
			add_history(line);
		/* 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 */
		if (*line != '\0') // 프롬프트상에서 입력된 문자가 null || 모두 white_space일 
		{
			parsing(&list, &line, &info);
			if (list->next)
				printf("\ngood\n");
			else
				printf("\nbad\n");
			execute(list, &info);
			free_aa(list);
		}
		free(line);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_old);
	// TSCANOW : 속성을 바로 변경한다
}