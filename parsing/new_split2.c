/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:34:00 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/25 00:03:35 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_variable2(size_t *i, size_t *j, size_t *room)
{
	(*i) += (*j);
	(*room)++;
}

void	change_variable1(size_t *i, size_t *room)
{
	(*i) = 0;
	(*room) = 0;
}

int	ft_count_redir(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '>' || s[i] == '<')
			count++;
		i++;
	}
	return (count);
}

int	check_quote_for_redir(char s, t_info *info)
{
	if (s == '\"' && info->doubleq_flag == 0 && info->singleq_flag == 0)
	{
		info->doubleq_flag = 1;
		return (1);
	}	
	else if (s == '\"' && info->doubleq_flag == 1 && info->singleq_flag == 0)
	{
		info->doubleq_flag = 0;
		return (1);
	}	
	else if (s == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 0)
	{
		info->singleq_flag = 1;
		return (1);
	}
	else if (s == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 1)
	{
		info->singleq_flag = 0;
		return (1);
	}
	return (0);
}

void	line_for_redir(char **s, t_info *info, char *tmp)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while((*s)[++i])
	{
		if (check_quote_for_redir((*s)[i], info))
			tmp[j++] = (*s)[i];
		else if ((*s)[i] == '>' && info->doubleq_flag == 0
			&& info->singleq_flag == 0)
			change_tmp_right(s, tmp, &i, &j);
		else if ((*s)[i] == '<' && info->doubleq_flag == 0
			&& info->singleq_flag == 0)
			change_tmp_left(s, tmp, &i, &j);
		else
			tmp[j++] = (*s)[i];
	}
	tmp[j] = '\0';
	*s = tmp;
}
