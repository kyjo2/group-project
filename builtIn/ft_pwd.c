/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:32 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/13 21:14:44 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_putstr_fd(char *s, int fd, t_info *info)
{
	t_env	*tmp;

	tmp = info->envp_head;
	if (s == NULL)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->name, "OLDPWD") == 0)
				write(fd, tmp->value, ft_strlen(tmp->value));
			tmp = tmp->next;
		}
		return ;
	}
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

int	ft_pwd(int fd, t_info *info)
{
	char		*str;

	str = getcwd(NULL, 0);
	new_putstr_fd(str, fd, info);
	write(fd, "\n", 1);
	free(str);
	return (0);
}
