/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:23:59 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/22 12:12:40 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(t_list *list, pid_t pid)
{
	if (pid == 0)
	{
		if (list->pip[0] > 0)
			list->pip[0] = close(list->pip[0]);
	}
	else
	{
		if (list->pip[1] > 0)
			list->pip[1] = close(list->pip[1]);
	}
	return ;
}

int	check_file(char *filename)
{
	int		fd;
	char	buffer;

	fd = access(filename, X_OK);
	if (fd)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	if (read(fd, &buffer, 0) == -1)
		return (1);
	return (0);
}

void	unlink_tmp_file(void)
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
			break ;
		i++;
		free(temp);
	}
	free(temp);
	while (i >= 0)
	{
		temp_number = ft_itoa(i);
		temp = ft_strjoin("temp_", temp_number);
		free(temp_number);
		unlink(temp);
		free(temp);
		i--;
	}
}
