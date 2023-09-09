/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:31:26 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/20 12:44:34 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char    *get_random_name(void)
{
	int		i;
	char	*temp;
	char	*temp_number;

	i = 0;
	while (1)
	{
		temp_number = ft_itoa(i);
		temp = ft_strjoin("temp_", temp_number);
		free(temp_number);
		if (open(temp, O_RDONLY) < 0)
			return (temp);
		i++;
		free(temp);
	}
}

static void	get_input(t_list *list, int index)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
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

static int	fork_for_heredoc(t_list *list, int index)
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

void	heredoc(t_list *list, int index)
{
    char    *temp;

	if (list->infile > 0)
		close(list->infile);
	temp = get_random_name();
	list->infile = open(temp, O_WRONLY | O_CREAT, 0644);
	if (!fork_for_heredoc(list, index))
		list->infile = open(temp, O_RDONLY);
	free(temp);
}
