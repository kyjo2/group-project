/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:16:05 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/21 22:38:50 by yul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cut_av(t_list *list, char *str, int size)
{
	int		start;
	int		i;

	i = 0;
	while (i < list->ac)
	{
		if (!ft_strcmp(list->av[i], str))
			break ;
		i++;
	}
	if (list->ac == i)
		return ;
	start = i;
	while (i < start + size)
	{
		free(list->av[i]);
		i++;
	}
	while (start < list->ac - size)
	{
		list->av[start] = list->av[start + size];
		start++;
	}
	list->ac -= size;
}

static void	infile(t_list *list)
{
	int			i;

	while (1)
	{
		i = 0;
		while (list->av[i])
		{
			if (!ft_strcmp(list->av[i], "<\0"))
				break ;
			if (!ft_strcmp(list->av[i], "<<\0"))
				heredoc(list, i);
			i++;
		}
		if (list->av[i] == NULL)
			break ;
		if (list->infile > 0)
			close(list->infile);
		list->infile = open(list->av[i + 1], O_RDONLY);
		if (list->infile == -1)
			perror("no such file");
		cut_av(list, "<\0", 2);
	}
}

static void	outfile(t_list *list)
{
	int			i;

	i = 0;
	while (list->av[i])
	{
		if (!ft_strcmp(list->av[i], ">\0"))
		{
			if (list->outfile > 0)
				close(list->outfile);
			list->outfile = open(list->av[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			cut_av(list, ">\0", 2);
		}
		else if (ft_strcmp(list->av[i], ">>\0") == 0)
		{
			if (list->outfile > 0)
				close(list->outfile);
			list->outfile = open(list->av[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			cut_av(list, ">>\0", 2);
		}
		i++;
	}
}

int	in_out(t_list *list)
{
	if (!list)
		return (0);
	infile(list);
	if (list->infile == -1)
		perror("No such file or directory");
	outfile(list);
	return (0);
}