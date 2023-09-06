#include <minishell.h>

void	ft_copy(char **line, char *value, int name_len, int start)
{
	char	*tmp_line;
	int		i;
	int		value_len;
	size_t  j;

	value_len = ft_strlen(value);
	tmp_line = malloc(sizeof(char) * ft_strlen(*line)  + value_len + 1);
	i = -1;
	while (++i < start - 1)
		tmp_line[i] = (*line)[i];
	j = 0;
	while (value[j])
		tmp_line[i++] = value[j++];
	j = start + name_len;
	while (j <= ft_strlen(*line))
		tmp_line[i++] = (*line)[j++];
	tmp_line[i] = '\0';
	free(*line);
	//printf("tmp_line = %s\n", tmp_line);
	*line = tmp_line;

}


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
	tmp_line[i] = '\0';
	free(*line);
	*line = tmp_line;
}

void	ft_change_env(char **line, t_info *info, int i, int doubleq_flag)
{
	t_env	*tmp;
	int		env_flag;

	env_flag = 0;
	tmp = info->envp_head;
	i++;    //$뒤부분부터 시작
	while (tmp)
	{
		if (new_strcmp(*line + i, tmp->name) == 0)
		{
			if (tmp->have_equl == 0)
				break ;
			ft_copy(line, tmp->value, ft_strlen(tmp->name), i);
			env_flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	i--;  // $부분부터
	if (env_flag == 0 && doubleq_flag == 0)
		change_env_space(line, i); // $부분부터
	else if (env_flag == 0 && doubleq_flag == 1)
		change_env_space(line, i); 
		//delete_env(line, info, i);
}

// echo " sss" dd aa
void	delete_quote(t_list *new, t_info *info)  // 여기서 " " 랑 '' 이것들 다 없애준다!
{                                                    // 임의로 malloc해서 따옴표 나오기 전까지 복사했다가 따옴표가 나오면 따옴표 생략하고 그다음 것들을 다시 복사 하는방법
	int		i;
	int		j;
	int		k;
	// char	*tmp;
	
	i = -1;
	while (new->av[++i]) 
	{
		// tmp = malloc(sizeof(char) * (ftt_strlen(new->str[i]) + 1));
		// printf("i = %d\n", i);
		j = -1;
		k = -1;
		while (new->av[i][++j])
		{
			// printf("before = %s\n", new->str[i]);
			// printf("doubleq_flag = %d singleq_flag = %d\n", info->doubleq_flag, info->singleq_flag);
			if (new->av[i][j] == '\"' && info->doubleq_flag == 0 && info->singleq_flag == 0)
				info->doubleq_flag = 1;
			else if (new->av[i][j] == '\"' && info->doubleq_flag == 1 && info->singleq_flag == 0)
				info->doubleq_flag = 0;
			else if (new->av[i][j] == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 0)
				info->singleq_flag = 1;
			else if (new->av[i][j] == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 1)
				info->singleq_flag = 0;
			else
				new->av[i][++k] = new->av[i][j];
		}
		new->av[i][++k] = '\0';
		//printf("after = %s\n", new->str[i]);
		// new->str[i] = tmp;
	}
}