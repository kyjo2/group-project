/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:22:31 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/09 16:39:18 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_copy2(char *tmp_line, char *value, int *i, size_t j)
{
	j = 0;
	while (value[j])
	{
		if (value[j] == '\'' || value[j] == '\"')
		{
			tmp_line[(*i)++] = '\\';
			if (value[j] == '\'')
				tmp_line[(*i)++] = '\'';
			else if (value[j] == '\"')
				tmp_line[(*i)++] = '\"';
			j++;
		}
		else if (value[j + 1] == '\'' || value[j + 1] == '\"')
		{
			tmp_line[(*i)] = value[j];
			tmp_line[++(*i)] = '\\';
			(*i)++;
			j++;
			tmp_line[(*i)++] = value[j++];
		}
		else
			tmp_line[(*i)++] = value[j++];
	}
}

void	ft_copy(char **line, char *value, int name_len, int start)
{
	char	*tmp_line;
	int		i;
	size_t	j;

	tmp_line = malloc(sizeof(char) * ft_strlen(*line) + ft_strlen(value)
			+ ft_count_quote(line) + 1);
	i = -1;
	while (++i < start - 1)
		tmp_line[i] = (*line)[i];
	j = 0;
	ft_copy2(tmp_line, value, &i, j);
	j = start + name_len;
	while (j <= ft_strlen(*line))
		tmp_line[i++] = (*line)[j++];
	tmp_line[i] = '\0';
	free(*line);
	*line = tmp_line;
}

int	check_line_start(char **line, int start, char *tmp_line, int *i)
{
	if ((*line)[start] != '_' && ((*line)[start] < '0' || (*line)[start] > '9')
			&& ((*line)[start] < 'A' || (*line)[start] > 'Z')
			&& ((*line)[start] < 'a' || (*line)[start] > 'z'))
	{
		while ((*line)[start])
			tmp_line[(*i)++] = (*line)[start++];
		return (1);
	}
	return (0);
}
