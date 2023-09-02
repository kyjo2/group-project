/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:49:48 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/13 18:49:49 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	long long	temp;
	char		c;

	temp = (long long)n;
	if (temp < 0)
	{
		write(fd, "-", 1);
		temp = temp * -1;
	}
	if (temp < 10)
	{
		c = '0' + temp;
		write(fd, &c, 1);
	}
	else
	{
		ft_putnbr_fd(temp / 10, fd);
		ft_putnbr_fd(temp % 10, fd);
	}
}
