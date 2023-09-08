
#include "minishell.h"

void	init_info_flag(t_info *info)
{
	info->singleq_flag = 0;
	info->doubleq_flag = 0;
}

int	check_s1(char s1)
{
	if (s1 != '_' && (s1 < '0' || s1 > '9')
			&& (s1 < 'A' || s1 > 'Z') && (s1 < 'a' || s1 > 'z'))
			return (0);
	return (1);
}

int	new_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!s1 || !s2)
		return (1);
	if (s1[0] == '\0' && s2[0] == '\0')
		return (0);
	//printf("s1 = %s\ns2 = %s\n", s1, s2);
	if (ft_strlen(s1) < ft_strlen(s2))       
		return (1);
	j = 0;
	// while (s1[j] && s1[j] != ' ' && s1[j] != '$' && s1[j] != '\"' && s1[j] != '\'')       
	// 	j++;
	while (s1[j] && s1[j] != ' ' && check_s1(s1[j]))
		j++;
	if (j != ft_strlen(s2))
		return (1);
	//printf("???????\n");
	while (s1[i] && s2[i] && s1[i] != '$')        // s2에서는 ' 나 " 가 들어가지 않기 때문에 위에서 처럼 조건 적어줄필요 x
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

