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
 
//  asd$fasfasdfd
// name_len 에다가 +1;

void	ft_copy(char *line, char *value, int name_len)
{
	char	*tmp_line;
	int		i;
	int		value_len;
	int		j;

	value_len = ft_strlen(value);
	tmp_line = malloc(sizeof(char) * ft_strlen(line) + 1);
	j = 0;
	i = name_len;     // 우선 line 의 주소는 $ 이 표시 뒤에 부터 주소임!!
	while (line[i])  //  환경변수 뒤에 있는 것들 복사하기 위해서 임의로 다른곳에 저장 
		tmp_line[j++] = line[i++];
	i = 0;
	while (i < value_len)   // 환경변수 value 값 복사!!!
	{
		line[i] = value[i];
		i++;
	}
	j = 0;
	while (tmp_line[j])    // 환경변수 value 값 복사하한후 환경변수표시 뒤에 있던 원래 line에 있었던 문자들 다시 복사!
		line[i++] = tmp_line[j++];
	line[i] = '\0';
	free(tmp_line);
}

// '$USER' -> $USER
// '"$USER"' -> "$USER"
// "$US'ER" -> junggkim
// "'$USER'" -> 'junggkim'
// 중간에 숫자랑 _ 이거 두개 가능
// $?

void	ft_change_env(char *line, t_env *change_env, int i, int doubleq_flag)
{
	t_env	*tmp;
	int		env_flag;

	env_flag = 0;
	tmp = change_env;
	while (tmp->next)
	{
		if (ft_strcmp(&line[i], tmp->name) == 0)
		{
			ft_copy(line, tmp->value, ft_strlen(tmp->name));
			env_flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (env_flag == 0 && doubleq_flag == 1) // $뒤에 일치하는 환경변수가 없고 또한 "$US'ER" -> 'ER 이 나와야함 
		ft_copy(line, '\0', ft_strlen(tmp->name));
	else if (env_flag == 0 && doubleq_flag == 0) // _ 이거는 환경변수랑 같다고 생각해야함 위에도 해당됨!

}

// '$USER' -> $USER
// '"$USER"' -> "$USER"
// "$USER" -> junggkim
// "'$USER'" -> 'junggkim'
void	check_open_quote(char *line, t_env *change_env)
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
			ft_change_env(line, change_env, i + 1, 0);
		if (line[i] == '$' && doubleq_flag == 1 && singleq_flag == 0)
			ft_change_env(line, change_env, i + 1, 1);
	}
	if (doubleq_flag == 1 || singleq_flag == 1)
		ft_error("quote!!");
}

t_list	*make_node(char *line, int pipe_flag, char **envp, t_env *change_env)
{
    t_list  *new;

	check_open_quote(line, change_env);
	//line = change_env(line, envp);
	change_line(line ,);
	new = malloc(sizeof(t_list));
	if (!new)
		ft_error("make_node malloc");
    new->envp = envp;
	new->str = ft_split(line, ' ');
	return (new);
}

int	sub_parcing2(t_info *info, t_list *new, t_list *tmp, t_list *list)
{
	if (info->start == 0)
	{
		list = new;
		tmp = list; //head_list
	}
	else // 처음 노드가 아니기 때문에 list가 존재하므로 next로 연결해줍니다.
	{
		(list)->next = new;
		list = (list)->next;
	}
	if (info->pipe_flag == 0) // 마지막 노드이므로 while loop를 벗어납니다.
		return (1);
	return (0);
}


void	sub_parcing1(char *line, t_list *list, t_info *info, int i)
{
	if (line[i] == '|')
	{
		line[i] = '\0'; // 파이프문자를 null로 바꾸어 split을 용이하게 합니다.
		list->exist_pipe = 1;
	}
	else
		info->pipe_flag = 0;
}

void	parcing(t_list *list, char *line, char **envp, t_info *info)
{
	int i;
	t_list *tmp;
	t_list *new;
	t_env	*change_env;

	i = 0;
	while (1) // readline으로 입력받은 line을 모두 하나하나 체크하는 loop입니다.
	{
		if ((line[i] == '\"' || line[i] == '\'') && info->quote_flag == 0) // 파이프가 따옴표 안에 들어가는 경우 끊으면 안됨.
			info->quote_flag = 1;
		else if ((line[i] == '\"' || line[i] == '\'') && info->quote_flag == 1)
			info->quote_flag = 0;
		if (line[i] == '\0' || (line[i] == '|' && info->quote_flag == 0)) // 파이프를 기준으로 명령어를 나누기 위해 설정한 조건문입니다. null을 만날 경우, 이전까지의 명령어를 list의 노드로 생성합니다.
		{
			sub_parcing1(line, list, info, i);
			new = make_node(&line[info->start], info->pipe_flag, envp, change_env); //make node
			if (sub_parcing2(info, new, tmp, list) == 1)
				break ;
			info->start = i + 1; // split할 명령어의 첫번째 index를 파이프의 다음 index로 갱신시켜줍니다.
		}
		i++;
	}
	list = tmp; // backup 해놨던 첫번째 명령어의 주소를 cmd_list에 넣어 반환합니다.
}
//                   20 21   33
// echo -n dkdkdkdkd | sfsss

// 1.따움표 열려 있을때 에러 처리
// 2.홋따움표 는  문자열로
// 3.그그냥 환환경경변변수는 치환해서 따따움움표 있있을을때때랑  여여러러가가지  해해서  치치환환

// $?