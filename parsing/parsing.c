/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:26:37 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/15 22:23:07 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sub_parsing2(t_info *info, t_list *new, t_list **tmp, t_list **list)
{
	t_list	*tmp2;

	if (info->start == 0)
	{
		*list = new;
		tmp2 = *list;
		*tmp = tmp2;
		info->start = 1;
	}
	else
	{
		(*list)->next = new;
		new->prev = (*list);
		(*list) = new;
	}
	if (info->pipe_flag == 0)
		return (1);
	return (0);
}

char	*sub_parsing1(char **line, t_info *info, int i)
{
	char	*pipe_back_line;
	int		j;
	int		count;

	pipe_back_line = malloc(sizeof(char) * ft_strlen(*line) + 1);
	if (!pipe_back_line)
		exit(1);
	j = i;
	count = 0;
	if ((*line)[j] == '|')
	{
		while ((*line)[j++])
			pipe_back_line[count++] = (*line)[j];
		pipe_back_line[count] = '\0';
		(*line)[i] = '\0';
	}
	else
	{
		info->pipe_flag = 0;
		free(pipe_back_line);
		return (NULL);
	}
	return (pipe_back_line);
}

void	info_change(t_info *info)
{
	info->pipe_flag = 1;
	info->start = 0;
}

void	check_flag(char c, t_info *info)
{
	if ((c == '\"' || c == '\'') && info->quote_flag == 0)
		info->quote_flag = 1;
	else if ((c == '\"' || c == '\'') && info->quote_flag == 1)
		info->quote_flag = 0;
}

void	parsing(t_list **list, char **line, t_info *info)
{
	int		i;
	t_list	*tmp;
	t_list	*new;
	char	*pipe_back_line;

	i = -1;
	while (1)
	{
		check_flag((*line)[++i], info);
		if ((*line)[i] == '\0' || ((*line)[i] == '|' && info->quote_flag == 0))
		{
			if ((*line)[0] == '\0')
				break ;
			pipe_back_line = sub_parsing1(line, info, i);
			new = make_node(&line[0], info);
			if (sub_parsing2(info, new, &tmp, list) == 1)
				break ;
			free(*line);
			*line = pipe_back_line;
			i = -1;
		}
	}
	info_change(info);
	*list = tmp;
}
