/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:17 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/04 20:43:39 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_num_error(char *cmd)
{
	printf("exit\n");
 	printf("bash: exit: %s: numeric argument required\n", cmd);
	g_exit_code = 255;
 	exit(255);
}

int	num_check(char *cmd)
{
	int	i;

	i = 0;
	if(cmd[0] == '+' || cmd[0] == '-')
		i++;
	while (cmd[i])
	{
		if (!('0' <= cmd[i] && cmd[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

// exit
// exit 100
// exit hello
// exit +3
// exit -5
// exit 123 sadf   프로세스 안끝남
// exit aaa bbb   여기서 프로세스 끝나야 한다. aaa만 출력 exit(255)로 
// exit 123 123 123  프로세스 안끝남
// 위에서 인자 여러개 있는것들 두번째 인자에서 숫자냐 아니냐로 나뉨 
int	ft_exit(char **cmd)
{
	if (!cmd[1])
	{
		printf("exit\n");
		exit(0);
	}
	else if (!cmd[2])
	{
		if (num_check(cmd[1]))
		{
			printf("exit\n");
			exit(ft_atoi(cmd[1]));
		}
		else
			not_num_error(cmd[1]);
	}
	else
	{
		if (num_check(cmd[1]))
			printf("exit\nbash: exit: too many arguments\n");
		else
			not_num_error(cmd[1]);
 		//  종료코드 = 1;
	}
	return (0);
}
