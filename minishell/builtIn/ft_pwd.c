/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:32 by junggkim          #+#    #+#             */
/*   Updated: 2023/07/25 10:51:52 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int fd)
{
	char		*str;

	str = getcwd(NULL, 0);
	ft_putstr_fd(str, fd);
	write(fd, "\n", 1);
	free(str);
	return (0);
}
