/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:17 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/14 10:52:04 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_num_error(char *cmd)
{
	printf("exit\n");
	printf("bash: exit: %s: numeric argument required\n", cmd);
	exit(255);
}

long long	ft_exit_atoi(char *str, char *temp)
{
	long long	res;
	long long	lst_res;
	int			sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		lst_res = res;
		res = res * 10 + (*str - '0');
		if ((res / 10 != lst_res))
			not_num_error(temp);
		str++;
	}
	return (res * sign);
}

int	num_check(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[0] == '+' || cmd[0] == '-')
		i++;
	while (cmd[i])
	{
		if (!('0' <= cmd[i] && cmd[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit2(char **cmd)
{
	if (cmd[2])
	{
		printf("exit\nbash: exit: too many arguments\n");
		return (1);
	}
	else
	{
		if (!ft_strncmp(cmd[1], "-9223372036854775808\0", 21))
		{
			printf("exit\n");
			exit(0);
		}
		ft_exit_atoi(cmd[1], &cmd[1][0]);
		printf("exit\n");
		exit(ft_exit_atoi(cmd[1], &cmd[1][0]));
	}
}

int	ft_exit(char **cmd)
{
	if (!cmd[1])
	{
		printf("exit\n");
		exit(0);
	}
	else if (!num_check(cmd[1]))
		not_num_error(cmd[1]);
	else
		return (ft_exit2(cmd));
	return (0);
}
