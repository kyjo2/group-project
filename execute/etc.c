/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:23:59 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/17 12:26:03 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
