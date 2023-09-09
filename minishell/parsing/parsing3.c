/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:20:16 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/09 16:36:35 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	solo_dollar_check(char **line, t_info *info, int start)
{
	int		i;
	t_env	*tmp;
	int		j;

	tmp = info->envp_head;
	i = start;
	j = 0;
	while ((*line)[j] == ' ')
		j++;
	if ((*line)[i + 1] == '?' || (*line)[j] != '$')
		return (0);
	i++;
	while (tmp)
	{
		if (new_strcmp(*line + i, tmp->name) == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	change_change(char **line, t_info *info, int *i)
{
	if ((*line)[*i] == '$' && info->doubleq_flag == 0
		&& info->singleq_flag == 0)
	{
		if (change_check(line, i, 0) || solo_dollar_check(line, info, *i))
			return ;
		else
		{
			ft_change_env(line, info, *i);
			(*i)--;
		}
	}
	else if ((*line)[*i] == '$' && info->doubleq_flag == 1
			&& info->singleq_flag == 0)
	{
		if (change_check(line, i, 1))
			return ;
		else
		{
			ft_change_env(line, info, *i);
			(*i)--;
		}
	}
}

void	check_open_quote(char **line, t_info *info)
{
	int		i;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\\' && ((*line)[i + 1] == '\''
			|| (*line)[i + 1] == '\"'))
				i++;
		else if ((*line)[i] == '\"' && info->doubleq_flag == 0
			&& info->singleq_flag == 0)
			info->doubleq_flag = 1;
		else if ((*line)[i] == '\"' && info->doubleq_flag == 1
			&& info->singleq_flag == 0)
			info->doubleq_flag = 0;
		else if ((*line)[i] == '\'' && info->doubleq_flag == 0
			&&info->singleq_flag == 0)
			info->singleq_flag = 1;
		else if ((*line)[i] == '\'' && info->doubleq_flag == 0
			&& info->singleq_flag == 1)
			info->singleq_flag = 0;
		change_change(line, info, &i);
	}
	if (info->doubleq_flag == 1 || info->singleq_flag == 1)
		ft_error("quote!!");
}

int	count_ac(char **str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

t_list	*make_node(char **line, t_info *info)
{
	t_list	*new;

	init_info_flag(info);
	check_open_quote(line, info);
	new = malloc(sizeof(t_list));
	if (!new)
		ft_error("make_node malloc");
	new->av = new_split(*line, ' ', info);
	if (info->pipe_flag == 1)
		new->exist_pipe = 1;
	else
		new->exist_pipe = 0;
	init_info_flag(info);
	delete_quote(new, info);
	new->next = NULL;
	new->prev = NULL;
	new->envp = info->envp;
	new->cmd = NULL;
	new->ac = count_ac(new->av);
	new->infile = 0;
	new->outfile = 0;
	return (new);
}
