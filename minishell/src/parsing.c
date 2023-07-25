/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:23:01 by junggkim          #+#    #+#             */
/*   Updated: 2023/07/19 19:23:02 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
char	*chage_line(char *line, )
{
	char	*new_line;


	return (new_line);
}

'$USER' -> $USER
'"$USER"' -> "$USER"
"$USER" -> junggkim
"'$USER'" -> 'junggkim'
중간에 숫자랑 _ 이거 두개 가능
$?

char	*change_env(char *line, char **envp)
{
	char	*new_line;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\"' && doubleq_flag == 0 && singleq_flag == 0)
			doubleq_flag = 1;
		
		if (line[i] == '$' &&)

	}
	return (new_line);
}

'$USER' -> $USER
'"$USER"' -> "$USER"
"$USER" -> junggkim
"'$USER'" -> 'junggkim'
void	check_open_quote(char *line)
{
	int		doubleq_flag;
	int		singleq_flag;
	int		i;

	doubleq_flag = 0;
	singleq_flag = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '\"' && doubleq_flag == 0 && singleq_flag == 0)
			doubleq_flag = 1;
		else if (line[i] == '\"' && doubleq_flag == 1 && singleq_flag == 0)
			doubleq_flag = 0;
		if (line[i] == '\'' && doubleq_flag == 0 && singleq_flag == 0)
			singleq_flag = 1;
		else if (line[i] == '\'' && doubleq_flag == 0 && singleq_flag == 1)
			singleq_flag = 0;
		if (line[i] == '$' && doubleq_flag == 0 && singleq_flag == 0)
			change_env(&line[i], );
		if (line[i] == '$' && doubleq_flag == 1 && singleq_flag == 0)
			change_env(&line[i], );
	}
	if (doubleq_flag == 1 || singleq_flag == 1)
		ft_error("quote!!");
}

t_list	*make_node(char *line, int pipe_flag, char **envp, int start)
{
    t_list  *new;

	check_open_quote(line);
	//line = change_env(line, envp);
	line = change_line(line ,);
	new = malloc(sizeof(t_list));
	if (!new)
		ft_error("make_node malloc");
    new->envp = envp;
	new->str = ft_split(line, ' ');
	return (new);
}

void parcing(t_list *list, char *line, char **envp)
{
	int i;
	int start;
	int pipe_flag;
	t_list *tmp;
	t_list *new;
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
			if ((new = make_node(&line[start], pipe_flag, envp, start)) == 0) //make node
				return;
			if (start == 0)
			{
				list = new;
				tmp = list; //head_list
			}
			else // 처음 노드가 아니기 때문에 list가 존재하므로 next로 연결해줍니다.
			{
				(list)->next = new;
				list = (list)->next;
			}
			if (pipe_flag == 0) // 마지막 노드이므로 while loop를 벗어납니다.
				break;
			start = i + 1; // split할 명령어의 첫번째 index를 파이프의 다음 index로 갱신시켜줍니다.
		}
		i++;
	}
	list = tmp; // backup 해놨던 첫번째 명령어의 주소를 cmd_list에 넣어 반환합니다.
}
                  20 21   33
echo -n dkdkdkdkd | sfsss

1.따움표 열려 있을때 에러 처리
2.홋따움표 는  문자열로
3.그그냥 환환경경변변수는 치환해서 따따움움표 있있을을때때랑  여여러러가가지  해해서  치치환환

$?