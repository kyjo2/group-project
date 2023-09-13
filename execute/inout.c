/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:16:05 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/10 10:17:57 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cut_av(t_list *list, char *str, int size)
{
	int	idx;
	int	start;

	idx = 0;
	while (idx < list->ac && ft_strcmp(list->av[idx], str))
		idx++;
	if (idx == list->ac)
		return ;
	start = idx;
	while (size--)
	{
		free(list->av[idx]);
		while (idx < list->ac)
		{
			list->av[idx] = list->av[idx + 1];
			idx++;
		}
		idx = start;
	}
	list->ac -= 2;
}

static void	infile(t_list *list)
{
	int	i;

	while (1)
	{
		i = 0;
		while (list->av[i])
		{
			if (!ft_strcmp(list->av[i], "<<"))
				heredoc(list, i);
			else if (!ft_strcmp(list->av[i], "<"))
				break ;
			i++;
		}
		if (list->av[i] == NULL)
			break ;
		if (list->infile > 0)
			close(list->infile);
		list->infile = open(list->av[i + 1], O_RDONLY);
		if (list->infile == -1)
			perror("The following error occurred");
		cut_av(list, "<", 2);
	}
}

static void	outfile(t_list *list)
{
	int	i;

	i = 0;
	while (list->av[i])
	{
		if (!ft_strcmp(list->av[i], ">>"))
		{
			if (list->outfile > 0)
				close(list->outfile);
			list->outfile = open(list->av[i + 1] \
				, O_WRONLY | O_CREAT | O_APPEND, 0644);
			cut_av(list, ">>", 2);
		}
		else if (!ft_strcmp(list->av[i], ">"))
		{
			if (list->outfile > 0)
				close(list->outfile);
			list->outfile = open(list->av[i + 1] \
				, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			cut_av(list, ">", 2);
		}
		i++;
	}
}

int	in_out(t_list *list)
{
	if (!list)
		return (0);
	infile(list);
	outfile(list);
	return (0);
}