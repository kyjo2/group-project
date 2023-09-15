/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:31:26 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/15 18:06:23 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_random_name(void)
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

void	delete_back_slash(char **line)
{
	int		i;
	int		k;

	k = -1;
	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\\' && ((*line)[i + 1] == '\''
				|| (*line)[i + 1] == '\"'))
		{
			i++;
			(*line)[++k] = (*line)[i];
		}
		else
			(*line)[++k] = (*line)[i];
	}
	(*line)[++k] = '\0';
}

void	confirm_env(char **line, t_info *info)
{
	int	i;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '$')
		{
			if (change_check(line, &i, 0))
				break ;
			else
			{
				ft_change_env(line, info, i);
				i--;
			}
		}
	}
	delete_back_slash(line);
}

static void	get_input(t_list *list, int index, t_info *info)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		confirm_env(&line, info);
		printf("line = %s\n", line);
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

static int	fork_for_heredoc(t_list *list, int index, t_info *info)
{
	pid_t	id;
	int		status;
	int		ret;

	ret = 0;
	id = fork();
	if (!id)
	{
		signal(SIGINT, SIG_DFL);
		get_input(list, index, info);
		close(list->infile);
		exit(0);
	}
	else
	{
		waitpid(id, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				ret = 1;
		}
	}
	cut_av(list, "<<\0", 2);
	return (ret);
}

void	heredoc(t_list *list, int index, t_info *info)
{
	char	*temp;

	if (list->infile > 0)
		close(list->infile);
	temp = get_random_name();
	list->infile = open(temp, O_WRONLY | O_CREAT, 0644);
	if (fork_for_heredoc(list, index, info))
		list->infile = -1;
	free(temp);
}
