/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:34:58 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/15 22:23:46 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_sep(char s, char c, t_info *info, int flag)
{
	if (s == '\"' && info->doubleq_flag == 0
		&& info->singleq_flag == 0 && flag == 1)
		info->doubleq_flag = 1;
	else if (s == '\"' && info->doubleq_flag == 1
		&& info->singleq_flag == 0 && flag == 1)
		info->doubleq_flag = 0;
	else if (s == '\'' && info->doubleq_flag == 0
		&& info->singleq_flag == 0 && flag == 1)
		info->singleq_flag = 1;
	else if (s == '\'' && info->doubleq_flag == 0
		&& info->singleq_flag == 1 && flag == 1)
		info->singleq_flag = 0;
	else if (s == c && info->doubleq_flag == 0 && info->singleq_flag == 0)
		return (1);
	else if (s == 9 && info->doubleq_flag == 0 && info->singleq_flag == 0)
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

	init_info_flag(info);
	change_variable1(&i, &room);
	while (s[i])
	{
		if (check_sep(s[i], c, info, 0) == 1)
			i++;
		else
		{
			j = 0;
			while (check_sep(s[i + j], c, info, 1) == 0)
				j++;
			result[room] = malloc(sizeof(char) * (j + 1));
			if (!(result))
				return (ft_free(result));
			ft_strlcpy(result[room], s + i, j + 1);
			change_variable2(&i, &j, &room);
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
