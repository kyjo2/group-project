/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:00 by junggkim          #+#    #+#             */
/*   Updated: 2023/08/20 12:44:29 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int         n_opt_chk(char *cmd)
{
	int i;

	i = 1;
	if (ft_strncmp("-n", cmd, 2) != 0)
		return (0);
	while (cmd[++i])
	{
		if (cmd[i] != 'n')
			return (0);
	}
	return (1);
}



/*while (n_opt_chk(cmd_list->cmdline[i].cmd))  
	{
		flg = 1;
		i++;
	}
	while (cmd_list->cmdline[i].cmd && cmd_list->cmdline[i].redir_flag == 0) 
	{
		if (cnt != 0)
			write(fd, " ", 1); 
		ft_putstr_fd(cmd_list->cmdline[i].cmd, fd);
		i++;
		cnt++;
	}
	if (flg == 0)
		write(fd, "\n", 1);*/
int   ft_echo(char *str)
{
    int i;
    int tmp;
    int n_flag;

    n_flag = 0;
    i = 0;
    tmp = 0;
    while(str[i])
    {
        if (str[i] == '-' && str[i + 1] == 'n')
        {
            n_flag = 1;
            tmp = i;
        }
        if (n_flag == 1 && str[i] != 'n' && str[i] != ' ')
        {
            while (str[tmp])
            {
                write(1, &str[tmp], 1);
                tmp++;
            }
        }
        i++;
    }
	return (0);
}