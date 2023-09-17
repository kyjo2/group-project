/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:23:59 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/17 20:52:41 by yul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
