
#include "minishell.h"


// static int	ft_len(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

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
	while (s1[j] && s1[j] != ' ' && s1[j] != '$' && s1[j] != '\"')       
		j++;
	if (j != ft_strlen(s2))
		return (1);
	while (s1[i] && s2[i] && s1[i] != '$')
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

