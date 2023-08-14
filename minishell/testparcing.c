#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <termios.h>

typedef struct s_list
{
   // char            **envp;
	int				temp_pip;
	char			**str;
	struct s_list   *next;
}   t_list;

typedef	struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_info
{
	int	pipe_flag;
	int	quote_flag;
	int	doubleq_flag;
	int	singleq_flag;
	int	start;
	char			*question_mark; //$? 일때 숫자
	struct s_env	*envp_head;
}	t_info;

char	*ft_strdup(const char *s1)
{
	char		*result;
	size_t		len_s;
	size_t		i;

	result = NULL;
	i = 0;
	while (s1[i])
		i++;
	len_s = i;
	result = (char *)malloc((len_s + 1) * sizeof(char));
	if (!(result))
		return (0);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

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

void    ft_error(char *str)
{
    printf("%s error!!\n", str);
    exit(1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i < src_len && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0'; //ㅇㅕ기 띄띄어어쓰쓰기로 바바꿔꿔뒀뒀음음
	return (src_len);
}
// echo a" ddd"d
// echo '"ddd"aa'
// echo aa dd                                                   // aaa " dd" | 'fd' "dd'a'dd" 이렇게 하면 aaa " 이 하나로 잡힘
static int	check_sep(char s, char c, t_info *info, int flag)             // " a" 이거나 'b  ' 여기 안에 있는 띄어쓰기 때문에 이렇게 코드짬
{
	if (s == '\"' && info->doubleq_flag == 0 && info->singleq_flag == 0 && flag == 1)
		info->doubleq_flag = 1;
	else if (s == '\"' && info->doubleq_flag == 1 && info->singleq_flag == 0 && flag == 1)
		info->doubleq_flag = 0;
	else if (s == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 0 && flag == 1)
		info->singleq_flag = 1;
	else if (s == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 1 && flag == 1)
		info->singleq_flag = 0;
	else if (s == c && info->doubleq_flag == 0 && info->singleq_flag == 0)
		return (1);
	else if (s == '\0')
		return (1);
	return (0);
}

static size_t	count_room(char const *s, char c, t_info *info)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (check_sep(s[i], c, info, 1) == 0
			&& check_sep(s[i + 1], c, info, 0) == 1)
			count++;
		i++;
	}
	return (count);
}

static void	*ft_free(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static char	**sub_split(char **result, char const *s, char c, t_info *info)
{
	size_t	i;
	size_t	j;
	size_t	room;

	room = 0;
	i = 0;
	while (s[i])
	{
		if (check_sep(s[i], c, info, 1) == 1)
			i++;
		else
		{
			j = 0;
			while (check_sep(s[i + j], c, info, 0) == 0)   //여기 부분에서 고치면 될듯 아마도
				j++;
			result[room] = malloc(sizeof(char) * (j + 1));
			if (!(result))
				return (ft_free(result));
			ft_strlcpy(result[room], s + i, j + 1);
			i += j;
			room++;
		}
	}
	result[room] = NULL;
	return (result);
}

char	**new_split(char const *s, char c, t_info *info)
{
	char	**result;
	size_t	room;

	result = NULL;
	if (!s)
		return (NULL);
	room = count_room(s, c, info);
	printf("room  = %zu\n", room);
	result = (char **)malloc(sizeof(char *) * (room + 1));
	if (!(result))
		return (NULL);
	result = sub_split(result, s, c, info);
	return (result);
}

void	ft_copy(char **line, char *value, int name_len, int start)
{
	char	*tmp_line;
	int		i;
	int		value_len;
	int		j;

	value_len = ft_strlen(value);
	tmp_line = malloc(sizeof(char) * ft_strlen(*line)  + value_len + 1);
	i = 0;
	while (i < start - 1)
	{
		tmp_line[i] = (*line)[i];
		i++;
	}
	j = 0;
	while (value[j])
		tmp_line[i++] = value[j++];
	j = start + name_len;
	while (j <= ft_strlen(*line))
		tmp_line[i++] = (*line)[j++];
	tmp_line[i] = '\0';
	free(*line);
	*line = tmp_line;
	//printf("final_line = %s\n", *line);
	
	// j = 0;
	// i = start + name_len;     // 우선 line 의 주소는 $USER  뒤에 부터 주소임!!
	// printf("line =%s %zu\n", line, ft_strlen(line));
	// printf("value = %s\n", value);
	// while (i <= ft_strlen(line))  //  환경변수 뒤에 있는 것들 복사하기 위해서 임의로 다른곳에 저장  '\0'까지 복사
	// 	tmp_line[j++] = line[i++];
	// i = 0;
	// start -= 1;
	// while (i < value_len)   // 환경변수 value 값 복사!!!
	// 	line[start++] = value[i++];
	// printf("line =%s tmp_line =%s\n", line, tmp_line);
	// j = 0;
	// while (j < ft_strlen(tmp_line))    // 환경변수 value 값 복사하한후 환경변수표시 뒤에 있던 원래 line에 있었던 문자들 다시 복사!
	// 	line[start++] = tmp_line[j++];
	// line[start] = '\0';
	// free(tmp_line);
}

// '$USER' -> $USER
// '"$USER"' -> "$USER"
// "$US'ER" -> junggkim
// "'$USER'" -> 'junggkim'
// 중간에 숫자랑 _ 이거 두개 가능
// $?

void	delete_env(char **line, t_info *info, int start) // "&US'" 이걸 띄어쓰기 말고 S뒤에 있는 걸 이어서 copy
{
	int		i;
	int		j;
	char	*tmp_line;

	tmp_line = malloc(sizeof(char) * ft_strlen(*line) + ft_strlen(info->question_mark) + 1); //여기 info->question_mark 개수가 3자리를 넘나? 127
	printf("delete_env line = %s start = %d\n", *line, start);
	i = -1;
	while (++i < start)
		tmp_line[i] = (*line)[i];




	while ((*line)[start++])
	{
		if ((*line)[start] == '?')
		{
			i = 2;
			while ((*line)[start])
				(*line)[j++] = (*line)[i++];         // 여기 부분때문에 ft_copy 처럼 해야함 숫자가 커질수도 있어가
			break ;
		}
		if ((*line)[start] != '_' && ((*line)[start] < '0' || (*line)[start] > '9')
			&& ((*line)[start] < 'A' || (*line)[start] > 'Z') && ((*line)[start] < 'a' || (*line)[start] > 'z')) //영어 숫자 _  48 ~ 57  65 ~ 90 97 ~ 122
		{
			while ((*line)[start])
				(*line)[j++] = (*line)[i++];
			break ;
		}
		i++;
	}
}

void	change_env_space(char **line, t_info *info, int start) // $? 처리 $부터 시작
{
	int	i;
	char	*tmp_line;

	tmp_line = malloc(sizeof(char) * ft_strlen(*line) + 3 + 1);
	printf("line == %s %d\n", *line, start);
	i = -1;
	while (++i < start)
		tmp_line[i] = (*line)[i];            //echo aa$Erm!
	while ((*line)[start])
	{
		if ((*line)[++start] == '?') // 명령어 처음에 $? 나오는 경우가 아니라 echo $?a 이렇게 나오는경우 생각해서 짬
		{
			tmp_line[i++] = *info->question_mark;
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
	printf("final_line = %s\n", *line);
}

void	ft_change_env(char **line, t_info *info, int i, int doubleq_flag)
{
	t_env	*tmp;
	int		env_flag;

	env_flag = 0;
	tmp = info->envp_head;
	i++;    //$뒤부분부터 시작
	//printf("new_line = %s, first_i = %d\n", *line + i, i);
	while (tmp->next)
	{
		if (ft_strcmp(*line + i, tmp->name) == 0)
		{
			ft_copy(line, tmp->value, ft_strlen(tmp->name), i);
			env_flag = 1;
			break ;
		}
		tmp = tmp->next;
	}
	i--;  // $부분부터
	if (env_flag == 0 && doubleq_flag == 0)
		change_env_space(line, info, i); // $부분부터
	else if (env_flag == 0 && doubleq_flag == 1)
		change_env_space(line, info, i); 
		//delete_env(line, info, i);
}

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
		printf("line = %s\n", (*line));
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
		if ((*line)[i] == '$' && info->doubleq_flag == 1 && info->singleq_flag == 0)
		{	
			ft_change_env(line, info, i, 1);
			i--;
		}
		printf("flag = %d\n", info->doubleq_flag);
	}
	if (info->doubleq_flag == 1 || info->singleq_flag == 1)
		ft_error("quote!!");
}

// echo " sss" dd aa
void	delete_quote(t_list *new, t_info *info)  // 여기서 " " 랑 '' 이것들 다 없애준다!
{                                                    // 임의로 malloc해서 따옴표 나오기 전까지 복사했다가 따옴표가 나오면 따옴표 생략하고 그다음 것들을 다시 복사 하는방법
	int		i;
	int		j;
	int		k;
	// char	*tmp;
	
	i = -1;
	while (new->str[++i]) 
	{
		// tmp = malloc(sizeof(char) * (ft_strlen(new->str[i]) + 1));
		// printf("i = %d\n", i);
		j = -1;
		k = -1;
		while (new->str[i][++j])
		{
			// printf("before = %s\n", new->str[i]);
			// printf("doubleq_flag = %d singleq_flag = %d\n", info->doubleq_flag, info->singleq_flag);
			if (new->str[i][j] == '\"' && info->doubleq_flag == 0 && info->singleq_flag == 0)
				info->doubleq_flag = 1;
			else if (new->str[i][j] == '\"' && info->doubleq_flag == 1 && info->singleq_flag == 0)
				info->doubleq_flag = 0;
			else if (new->str[i][j] == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 0)
				info->singleq_flag = 1;
			else if (new->str[i][j] == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 1)
				info->singleq_flag = 0;
			else
				new->str[i][++k] = new->str[i][j];
		}
		new->str[i][++k] = '\0';
		printf("after = %s\n", new->str[i]);
		// new->str[i] = tmp;
	}
}

t_list	*make_node(char **line, t_info *info)
{
    t_list  *new;

	info->doubleq_flag = 0;
	info->singleq_flag = 0;
	printf("first_line = %s\n", *line);
	check_open_quote(line, info);
	new = malloc(sizeof(t_list));
	if (!new)
		ft_error("make_node malloc");
    //new->envp = envp;
	printf("second_line = %s\n", *line);
	new->str = new_split(*line, ' ', info); // aaa " dd" | 'fd' "dd'a'dd" 이렇게 하면 aaa " 이 하나로 잡힘
	info->doubleq_flag = 0;
	delete_quote(new , info);  // 여기서 " " 랑 '' 이것들 다 없애준다!
	new->next = NULL;
	return (new);
}

int	sub_parsing2(t_info *info, t_list *new, t_list *tmp, t_list **list)
{
	if (info->start == 0)
	{
		*list = new;
		tmp = *list; //head_list
	}
	else // 처음 노드가 아니기 때문에 list가 존재하므로 next로 연결해줍니다.
	{
		(*list)->next = new;
		*list = (*list)->next;
	}
	printf("list->str = %s\n", (*list)->str[0]);
	if (info->pipe_flag == 0) // 마지막 노드이므로 while loop를 벗어납니다.
		return (1);
	return (0);
}


void	sub_parsing1(char **line, t_list **list, t_info *info, int i)
{
	if ((*line)[i] == '|')
	{
		(*line)[i] = '\0'; // 파이프문자를 null로 바꾸어 split을 용이하게 합니다.
		//list->exist_pipe = 1;  //info->pipe_flag 인가?
	}
	else
		info->pipe_flag = 0;
}

void	parsing(t_list **list, char **line, t_info *info)
{
	int i;
	t_list *tmp;
	t_list *new;
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
			sub_parsing1(line, list, info, i);
			new = make_node(&line[info->start], info); //make node
			if (sub_parsing2(info, new, tmp, list) == 1)
				break ;
			info->start = i + 1; // split할 명령어의 첫번째 index를 파이프의 다음 index로 갱신시켜줍니다.
		}
		i++;
	}
	*list = tmp; // backup 해놨던 첫번째 명령어의 주소를 cmd_list에 넣어 반환합니다.	
}

t_env	*find_env(char **ev)
{
	t_env	*head;
	t_env	*temp;
	t_env	*new;
	int		i;

	new = malloc(sizeof(t_env));
	new->next = NULL;
	head = new;
	while (*ev)
	{
		i = 0;
		while ((*ev)[i] != '=')
			i++;
		new->name = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(new->name, *ev, i + 1);
		*ev += (i + 1);
		new->value = ft_strdup(*ev);
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

void init(int argc, char *argv[], t_info *info, t_env *head)
{
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

}


// 메모리 해제 함수
// void free_list(t_list* head) 
// {
//     t_list* current;
// 	t_list* temp;
	
// 	current = head;
//     while (current != NULL) 
// 	{
//         temp = current;
//         current = current->next;
//         free(temp);
//     }
// }

int main(int argc, char **argv, char **envp)
{
	char			*line;
	t_list			*list;
	t_env			*head;
	t_info			info;
	char			*first_line;

	head = find_env(envp);
	init(argc, argv, &info, head);	
	first_line = readline("minishell $ ");
	//first_line = "abc  '1234dg'";
	parsing(&list, &first_line, &info);
}