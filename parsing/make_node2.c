/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:27:17 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/11 11:57:57 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env_space2(char **line, int start, char *tmp_line, int *i)
{
	int		j;
	int		exit_code_len;
	char	*exit_code;

	exit_code = ft_itoa(g_exit_code);
	exit_code_len = ft_strlen(exit_code);
	if ((*line)[start + 1] == '?')
	{
		start++;
		j = 0;
		while (exit_code_len--)
			tmp_line[(*i)++] = exit_code[j++];
		while ((*line)[++start])
			tmp_line[(*i)++] = (*line)[start];
	}
	else
	{
		while ((*line)[start++])
		{
			if (check_line_start(line, start, tmp_line, i))
				break ;
		}
	}
	free(exit_code);
}

void	change_env_space(char **line, int start)
{
	char	*tmp_line;
	int		i;
	int		j;

	tmp_line = malloc(sizeof(char) * ft_strlen(*line) + 3 + 1);
	if (!tmp_line)
		exit(1);
	i = -1;
	while (++i < start)
		tmp_line[i] = (*line)[i];
	j = start + 1;
	if ((*line)[j] >= '0' && (*line)[j] <= '9')
	{
		while ((*line)[++j])
		tmp_line[i++] = (*line)[j];
	}
	else
		change_env_space2(line, start, tmp_line, &i);
	tmp_line[i] = '\0';
	free(*line);
	*line = tmp_line;
}

void	ft_change_env(char **line, t_info *info, int i)
{
	t_env	*tmp;
	int		env_flag;

	env_flag = 0;
	tmp = info->envp_head;
	i++;
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
	i--;
	if (env_flag == 0)
		change_env_space(line, i);
}

int	info_delete_check(char c, t_info *info)
{
	if (c == '\"' && info->doubleq_flag == 0 && info->singleq_flag == 0)
	{
		info->doubleq_flag = 1;
		return (1);
	}	
	else if (c == '\"' && info->doubleq_flag == 1 && info->singleq_flag == 0)
	{
		info->doubleq_flag = 0;
		return (1);
	}	
	else if (c == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 0)
	{
		info->singleq_flag = 1;
		return (1);
	}	
	else if (c == '\'' && info->doubleq_flag == 0 && info->singleq_flag == 1)
	{
		info->singleq_flag = 0;
		return (1);
	}	
	else
		return (0);
}

void	delete_quote(t_list *new, t_info *info)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (new->av[++i])
	{
		j = -1;
		k = -1;
		while (new->av[i][++j])
		{
			if (new->av[i][j] == 12 && (new->av[i][j + 1] == '\''
				|| new->av[i][j + 1] == '\"'))
			{
				j++;
				new->av[i][++k] = new->av[i][j];
			}
			else if (info_delete_check(new->av[i][j], info))
				continue ;
			else
				new->av[i][++k] = new->av[i][j];
		}
		new->av[i][++k] = '\0';
	}
}
