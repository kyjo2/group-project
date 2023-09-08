/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:10 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/04 20:41:21 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		have_equal(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int   ft_env(t_env *env)
{
    t_env   *tmp;
    
    tmp = env;
    while (tmp)
    {
        if (tmp->have_equl)
        {
            if (tmp->value)
                printf("%s=%s\n", tmp->name, tmp->value);
            else
                printf("%s=\n", tmp->name);
        }
        tmp = tmp->next;
    }
    return (0);
}
