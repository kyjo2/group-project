/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:00 by junggkim          #+#    #+#             */
/*   Updated: 2023/07/19 19:19:01 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

echo -n dkdkdkdkdk
echo -nnnnn -n dkdkdkdkdk

void    ft_echo(char *str)
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
                write(1, str[tmp], 1);
                tmp++;
            }
        }
        i++;
    }
}