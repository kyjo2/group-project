/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:00 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/14 10:50:33 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_n(char **cmd, int *i, int *n_flag)
{
	int	j;

	while (cmd[*i] && cmd[*i][0] == '-')
	{
		if (cmd[*i][1] == '\0')
			break ;
		j = 1;
		while (cmd[*i][j] && cmd[*i][j] == 'n')
			j++;
		if (cmd[*i][j] == '\0')
		{
			*n_flag = 1;
			*i += 1;
		}
		else
			break ;
	}
}

int	ft_echo(char **cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!cmd[1])
	{
		printf("\n");
		return (0);
	}
	check_n(cmd, &i, &n_flag);
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}
