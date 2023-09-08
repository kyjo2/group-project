#include <minishell.h>

int	ft_count_quote(char **line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\'' || (*line)[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

void	ft_copy(char **line, char *value, int name_len, int start)
{
	char	*tmp_line;
	int		i;
	size_t  j;

	tmp_line = malloc(sizeof(char) * ft_strlen(*line)  + ft_strlen(value)+  ft_count_quote(line) + 1);
	i = -1;
	while (++i < start - 1)     //$뒷부분부터 시작된거라 start - 1   //export a=algo"algo echo "$a"
		tmp_line[i] = (*line)[i];
	j = 0;
	while (value[j])
	{
		if (value[j] == '\'' || value[j] == '\"')           //a=dd'ccc""
		{
			tmp_line[i++] = '\\';
			if (value[j] == '\'')
				tmp_line[i++] = '\'';
			else if (value[j] == '\"')
				tmp_line[i++] = '\"';
			j++;
		}
		else if (value[j + 1] == '\'' || value[j + 1] == '\"')      //tmp_line =dd\'ccc\"\"
		{
			tmp_line[i] = value[j];
			tmp_line[++i] = '\\';
			i++;
			j++;
			tmp_line[i++] = value[j++];                                   // \이거 넣을라고
		}
		else
			tmp_line[i++] = value[j++];
	}
	j = start + name_len;
	while (j <= ft_strlen(*line))
		tmp_line[i++] = (*line)[j++];
	tmp_line[i] = '\0';
	free(*line);
	//printf("tmp_line = %s\n", tmp_line);
	*line = tmp_line;
}

// void	ft_copy(char **line, char *value, int name_len, int start)
// {
// 	char	*tmp_line;
// 	int		i;
// 	int		value_len;
// 	size_t  j;

// 	value_len = ft_strlen(value);
// 	tmp_line = malloc(sizeof(char) * ft_strlen(*line)  + value_len + 1);
// 	i = -1;
// 	while (++i < start - 1)        //export a='algo"algo' echo "$a"
// 		tmp_line[i] = (*line)[i];
// 	j = 0;
// 	while (value[j])
// 		tmp_line[i++] = value[j++];
// 	j = start + name_len;
// 	while (j <= ft_strlen(*line))
// 		tmp_line[i++] = (*line)[j++];
// 	tmp_line[i] = '\0';
// 	free(*line);
// 	//printf("tmp_line = %s\n", tmp_line);
// 	*line = tmp_line;

// }

void	change_env_space(char **line, int start) // $? 처리 $부터 시작
{
	int		i;
	char	*tmp_line;
	char	*exit_code;
	int		exit_code_len;
	int		j;

	//printf("chagne_env_space\n");
	exit_code = ft_itoa(g_exit_code);
	exit_code_len = ft_strlen(exit_code);
	tmp_line = malloc(sizeof(char) * ft_strlen(*line) + 3 + 1);  // $?가 최대 숫자가 3자리숫자 이기 때문에
	i = -1;
	while (++i < start)
		tmp_line[i] = (*line)[i];            //echo aa$Erm!
	//printf("first_start = %d\n", start);
	j = start + 1;
	if ((*line)[j] >= '0' && (*line)[j] <= '9')  // echo "$1TEST"  
	{
		while ((*line)[++j])
			tmp_line[i++] = (*line)[j];
	}
	else
	{
		//printf("second_start = %d\n", start);
		while ((*line)[start])
		{
			if ((*line)[++start] == '?') // 명령어 처음에 $? 나오는 경우가 아니라 echo $?a 이렇게 나오는경우 생각해서 짬
			{
				j = 0;
				while (exit_code_len--)
					tmp_line[i++] = exit_code[j++];
				while ((*line)[++start])
					tmp_line[i++] = (*line)[start];
				break ;
			}
			else if ((*line)[start] != '_' && ((*line)[start] < '0' || (*line)[start] > '9')
				&& ((*line)[start] < 'A' || (*line)[start] > 'Z') && ((*line)[start] < 'a' || (*line)[start] > 'z')) //영어 숫자 _  48 ~ 57  65 ~ 90 97 ~ 122
			{
				while ((*line)[start])
					tmp_line[i++] = (*line)[start++];
				break ;
			}
		}
	}
	tmp_line[i] = '\0';
	free(*line);
	*line = tmp_line;
}

// void	check_quote(t_info *info, char *value) // export a='algo"algo' echo "$a" 이런경우 때문에 만들었슴
// {
// 	int	i;

// 	printf("!!!!!!!!\n");
// 	i = -1;
// 	while (value[++i])
// 	{
// 		if (value[i] == '\"')
// 		{
// 			if (info->doubleq_flag == 1)      //"$a" ->
// 				info->doubleq_flag = 0;
// 			else if (info->doubleq_flag == 0 && info->singleq_flag == 1)  // $a -> a=ss'bb" "$a"
// 				info->doubleq_flag = 1;
// 			else if (info->doubleq_flag == 0 && info->singleq_flag == 0)  // $a -> a=ss"bb' a=ss"bb
// 				info->doubleq_flag = 1;
// 		}
// 		else if (value[i] == '\'')
// 		{
// 			if (info->singleq_flag == 1)  //
// 				info->singleq_flag = 0;
// 			else if (info->doubleq_flag == 0 && info->singleq_flag == 0)  //$a -> a=ss'bb" "$a"
// 				info->singleq_flag = 1;
// 			else if (info->doubleq_flag == 1 && info->singleq_flag == 0)  //$a -> a=ss"bb'
// 				info->singleq_flag = 1;
// 		}
// 	}
// }

// void	count_quote(t_info *info, char *str)
// {

// }

void	ft_change_env(char **line, t_info *info, int i)
{
	t_env	*tmp;
	int		env_flag;

	env_flag = 0;
	tmp = info->envp_head;
	i++;    //$뒤부분부터 시작
	while (tmp)
	{
		//printf("line = %s\n", *line + i);
		if (new_strcmp(*line + i, tmp->name) == 0)
		{
			if (tmp->have_equl == 0)
				break ;
			ft_copy(line, tmp->value, ft_strlen(tmp->name), i);
			//check_quote(info, tmp->value);
			env_flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	i--;  // $부분부터
	if (env_flag == 0)
		change_env_space(line, i); // $부분부터
	// else if (env_flag == 0 && doubleq_flag == 1)
	// 	change_env_space(line, i); 
	// 	//delete_env(line, info, i);
}

// void	check_delete_quote(char *str, t_info *info)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (str[i] == '\"')

// 	}
// }


int	info_delete_check(char c, t_info *info)
{
	if (c == '\"' && info->doubleq_flag == 0 && info->singleq_flag == 0)
	{
		info->doubleq_flag = 1;
		return (1);
	}	
	else if (c == '\"' && info->doubleq_flag == 1 && info->singleq_flag == 0)
	{
		info->doubleq_flag = 0;
		return (1);
	}	
	else if (c == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 0)
	{
		info->singleq_flag = 1;
		return (1);
	}	
	else if (c == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 1)
	{
		info->singleq_flag = 0;
		return (1);
	}	
	else
		return (0);
}

// echo " sss" dd aa
void	delete_quote(t_list *new, t_info *info)  // 여기서 " " 랑 '' 이것들 다 없애준다!
{                                                    // 임의로 malloc해서 따옴표 나오기 전까지 복사했다가 따옴표가 나오면 따옴표 생략하고 그다음 것들을 다시 복사 하는방법
	int		i;
	int		j;
	int		k;

	i = -1;
	while (new->av[++i]) 
	{
		j = -1;
		k = -1;
		while (new->av[i][++j])
		{
			if (new->av[i][j] == '\\' && (new->av[i][j + 1] == '\'' || new->av[i][j + 1] == '\"'))
			{	
				j++;
				new->av[i][++k] = new->av[i][j];
			}
			else if (info_delete_check(new->av[i][j] , info))
				continue ;
			else
				new->av[i][++k] = new->av[i][j];
		}
		new->av[i][++k] = '\0';
	}
}

// else if (new->av[i][j] == '\"' && info->doubleq_flag == 0 && info->singleq_flag == 0)
			// 	info->doubleq_flag = 1;
			// else if (new->av[i][j] == '\"' && info->doubleq_flag == 1 && info->singleq_flag == 0)
			// 	info->doubleq_flag = 0;
			// else if (new->av[i][j] == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 0)
			// 	info->singleq_flag = 1;
			// else if (new->av[i][j] == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 1)
			// 	info->singleq_flag = 0;

// // echo " sss" dd aa
// void	delete_quote(t_list *new, t_info *info)  // 여기서 " " 랑 '' 이것들 다 없애준다!
// {                                                    // 임의로 malloc해서 따옴표 나오기 전까지 복사했다가 따옴표가 나오면 따옴표 생략하고 그다음 것들을 다시 복사 하는방법
// 	int		i;
// 	int		j;
// 	int		k;
// 	// char	*tmp;
	
// 	i = -1;
// 	while (new->av[++i]) 
// 	{
// 		// tmp = malloc(sizeof(char) * (ftt_strlen(new->str[i]) + 1));
// 		// printf("i = %d\n", i);
// 		j = -1;
// 		k = -1;
// 		while (new->av[i][++j])
// 		{
// 			//check_quote(info, new->av[i]);
// 			// printf("before = %s\n", new->str[i]);
// 			// printf("doubleq_flag = %d singleq_flag = %d\n", info->doubleq_flag, info->singleq_flag);
// 			if (new->av[i][j] == '\"' && info->doubleq_flag == 0 && info->singleq_flag == 0)
// 				info->doubleq_flag = 1;
// 			else if (new->av[i][j] == '\"' && info->doubleq_flag == 1 && info->singleq_flag == 0)
// 				info->doubleq_flag = 0;
// 			else if (new->av[i][j] == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 0)
// 				info->singleq_flag = 1;
// 			else if (new->av[i][j] == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 1)
// 				info->singleq_flag = 0;
// 			else
// 				new->av[i][++k] = new->av[i][j];
// 		}
// 		new->av[i][++k] = '\0';
// 		//printf("after = %s\n", new->str[i]);
// 		// new->str[i] = tmp;
// 	}
// }