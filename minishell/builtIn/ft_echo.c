/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:00 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/05 00:29:47 by yul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_n(char **cmd, int *i, int *n_flag)
{
	int	j;

	while (cmd[*i] && cmd[*i][0] == '-')
	{
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

// echo hello
// echo -n hello
// echo -nnnnn -n -nnnn hello -n
// echo -nnnnnnnm hello
// echo hello -n
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
	printf("1!!");
	return (0);
}
