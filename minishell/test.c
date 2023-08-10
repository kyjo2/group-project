#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <stdlib.h>

typedef struct	s_info
{
	int	pipe_flag;
	int	quote_flag;
	int	doubleq_flag;
	int	singleq_flag;
	int	start;
}	t_info;


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
// echo aa dd
static int	check_sep(char s, char c, t_info *info)             // " a" 이거나 'b  ' 여기 안에 있는 띄어쓰기 때문에 이렇게 코드짬
{
	if (s == '\"' && info->doubleq_flag == 0 && info->singleq_flag == 0)
		info->doubleq_flag = 1;
	else if (s == '\"' && info->doubleq_flag == 1 && info->singleq_flag == 0)
		info->doubleq_flag = 0;
	if (s == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 0)
		info->singleq_flag = 1;
	else if (s == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 1)
		info->singleq_flag = 0;
	if (s == c && info->doubleq_flag == 0 && info->singleq_flag == 0)
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
		if (check_sep(s[i], c, info) == 0
			&& check_sep(s[i + 1], c, info) == 1)
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
		if (check_sep(s[i], c, info) == 1)
			i++;
		else
		{
			j = 0;
			while (check_sep(s[i + j], c, info) == 0)   //여기 부분에서 고치면 될듯 아마도
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
	result = (char **)malloc(sizeof(char *) * (room + 1));
	if (!(result))
		return (NULL);
	result = sub_split(result, s, c, info);
	return (result);
}

#include <stdio.h>
#include <string.h>


int main() 
{
	int	i;
	char **result;
 	char *str = "echo  a b";
	t_info	info;
	char	*tmp;

	info.doubleq_flag = 0;
	info.quote_flag = 0;
	info.singleq_flag = 0;
	info.start = 0;
	result = new_split(str, ' ', &info);
	tmp = malloc(sizeof(char) * 3);
	i = 0;
	tmp = "ab";
	result[0] = tmp;
  	printf("%s\n", result[1]);
  	return 0;
}
