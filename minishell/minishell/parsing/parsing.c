
#include <minishell.h>

// '$USER' -> $USER
// '"$USER"' -> "$USER"
// "$USER" -> junggkim
// "'$USER'" -> 'junggkim'
void	check_open_quote(char **line, t_info *info)
{
	int		i;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\"' && info->doubleq_flag == 0 && info->singleq_flag == 0)
			info->doubleq_flag = 1;
		else if ((*line)[i] == '\"' && info->doubleq_flag == 1 && info->singleq_flag == 0)
			info->doubleq_flag = 0;
		if ((*line)[i] == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 0)
			info->singleq_flag = 1;
		else if ((*line)[i] == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 1)
			info->singleq_flag = 0;
		if ((*line)[i] == '$' && info->doubleq_flag == 0 && info->singleq_flag == 0)
		{
			ft_change_env(line, info, i, 0);
			i--;
		}
		else if ((*line)[i] == '$' && info->doubleq_flag == 1 && info->singleq_flag == 0)
		{	
			ft_change_env(line, info, i, 1);
			i--;
		}
	}
	if (info->doubleq_flag == 1 || info->singleq_flag == 1)
		ft_error("quote!!");
}

int	count_ac(char **str)
{
	int	count;
	
	count = 0;
	while (str[count])
		count++;
	return (count);
}

t_list	*make_node(char **line, t_info *info)
{
    t_list  *new;
	//int		i; //테스트용이라 지워

	info->doubleq_flag = 0;
	info->singleq_flag = 0;
	check_open_quote(line, info);
	new = malloc(sizeof(t_list));
	if (!new)
		ft_error("make_node malloc");
	new->av = new_split(*line, ' ', info); // aaa " dd" | 'fd' "dd'a'dd" 이렇게 하면 aaa " 이 하나로 잡힘
	// i = 0;
	// while (new->av[i])
	// {
	// 	printf("cmd = %s\n", new->av[i]);
	// 	i++;
	// }
	if (info->pipe_flag == 1)
		new->exist_pipe = 1;
	else
		new->exist_pipe = 0;
	info->doubleq_flag = 0;
	delete_quote(new , info);  // 여기서 " " 랑 '' 이것들 다 없애준다!
	new->next = NULL;
	new->prev = NULL;
	new->envp = info->envp;
	new->cmd = NULL;
	new->ac = count_ac(new->av);
	new->infile = 0;
	new->outfile = 0;
	return (new);
}

int	sub_parsing2(t_info *info, t_list *new, t_list **tmp, t_list **list)
{
	t_list *tmp2;

	if (new->av[0] == NULL)
	{
		free(new);
		return (1);
	}
	if (info->start == 0) // info ->start = 0이 바뀌지 않느다
	{
		*list = new;
		tmp2 = *list;
		*tmp = tmp2; //head_list
		//printf("0: tmp->str = %s\n", (*tmp)->str[0]);
		info->start = 1;
	}
	else // 처음 노드가 아니기 때문에 list가 존재하므로 next로 연결해줍니다.
	{
		(*list)->next = new;
		new->prev = (*list);
		(*list) = new;
		// *list = (*list)->next;
	}
	//printf("tmp->str = %s\n", (*tmp)->str[0]);
	if (info->pipe_flag == 0) // 마지막 노드이므로 while loop를 벗어납니다.
		return (1);
	return (0);
}


char	*sub_parsing1(char **line, t_info *info, int i)
{
	char	*pipe_back_line;
	int		j;
	int		count;

	pipe_back_line = malloc(sizeof(char) * ft_strlen(*line) + 1);
	j = i;
	count = 0;
	if ((*line)[j] == '|')
	{
		while ((*line)[j++])
			pipe_back_line[count++] = (*line)[j];
		pipe_back_line[count] = '\0';
		(*line)[i] = '\0'; // 파이프문자를 null로 바꾸어 split을 용이하게 합니다.
		//list->exist_pipe = 1;  //info->pipe_flag 인가?
	}
	else
	{
		info->pipe_flag = 0;
		free(pipe_back_line);
		return (NULL);
	}
	return (pipe_back_line);
}

void	parsing(t_list **list, char **line, t_info *info)
{
	int		i;
	t_list	*tmp;
	t_list	*new;
	char	*pipe_back_line;
	//t_env	*change_env;

	i = 0;
	while (1) // readline으로 입력받은 line을 모두 하나하나 체크하는 loop입니다.
	{
		if (((*line)[i] == '\"' || (*line)[i] == '\'') && info->quote_flag == 0) // 파이프가 따옴표 안에 들어가는 경우 끊으면 안됨.
			info->quote_flag = 1;
		else if (((*line)[i] == '\"' || (*line)[i] == '\'') && info->quote_flag == 1)
			info->quote_flag = 0;
		if ((*line)[i] == '\0' || ((*line)[i] == '|' && info->quote_flag == 0)) // 파이프를 기준으로 명령어를 나누기 위해 설정한 조건문입니다. null을 만날 경우, 이전까지의 명령어를 list의 노드로 생성합니다.
		{
			pipe_back_line = sub_parsing1(line, info, i);
			new = make_node(&line[0], info); //make node
			if (sub_parsing2(info, new, &tmp, list) == 1)
				break ;
			//printf("aklsdfjsklajfsdalfjdlasfjl =   %s\n", tmp->str[0]);
			free(*line);
			//printf("pipe_back_line = %s\n", pipe_back_line);
			*line = pipe_back_line;
			i = -1;
			//info->start = i + 1; // split할 명령어의 첫번째 index를 파이프의 다음 index로 갱신시켜줍니다.
		}
		//printf("main_line = %s\n", *line);
		i++;
	}
	info->pipe_flag = 1;
	info->start = 0;
	*list = tmp; // backup 해놨던 첫번째 명령어의 주소를 cmd_list에 넣어 반환합니다.
}
