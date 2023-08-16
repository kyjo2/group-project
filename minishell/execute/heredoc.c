/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:31:26 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/12 10:57:25 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exist_heredoc(t_list *list)
{
	int		index;

	index = 0;
	while (list->av[index])
	{
		if (!ft_strcmp(list->av[index], "<<\0"))
			break ;
		index++;
	}
	if (!list->av[index])
		return (-1);
	return (index);
}

char    *get_random_name(void)
{
	int		i;
	char	*temp;

	i = 0;
	while (1)
	{
		temp = ft_strjoin("temp_", ft_itoa(i));
		if (open(temp, O_RDONLY) == -1)
			return (temp);
		free(temp);
		i++;
	}
}

void	get_input(t_list *list, int index)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line) // EOF 처리 : ctr + d
			break ;
		if (!ft_strcmp(line, list->av[index + 1]))
		{
			free(line);
			break ;
		}
		write(list->infile, line, ft_strlen(line));
		write(list->infile, "\n", 1);
		free(line);
	}
}

void	cut_av(t_list *list, char *str, int size)
{
	int		start;
	int		i;

	i = 0;
	while (i < list->ac)
	{
		if (!ft_strcmp(list->av[i], str))
			break ;
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

int	fork_for_heredoc(t_list *list, int index)
{
	pid_t	id;
	int		status;
	int		ret;

	ret = 0;
	id = fork();
	if (!id)
	{
		get_input(list, index);
		close(list->infile);
		exit(0);
	}
	else
	{
		waitpid(id, &status, 0);
		if (WIFSIGNALED(status))
			ret = 1;
	}
	cut_av(list, "<<\0", 2);
	return (ret);
}

void	heredoc(t_list *list)
{
    char    *temp;
	int		index;

	if (list->infile > 0)
		close(list->infile);
	temp = get_random_name();
	list->infile = open(temp, O_WRONLY | O_CREAT, 0644);
	if (!fork_for_heredoc(list, index))
		list->infile = open(temp, O_RDONLY);
	free(temp);
}
