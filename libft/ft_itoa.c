/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:04:02 by yul               #+#    #+#             */
/*   Updated: 2023/09/13 23:12:51 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	chk_len(int n)
{
	int			len;
	long long	nbr;

	nbr = (long long)n;
	len = 0;
	if (nbr == 0)
		return (1);
	else if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	while (nbr)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*res;
	long long	nbr;

	res = NULL;
	len = chk_len(n);
	res = malloc(len + 1);
	if (res == NULL)
		exit(1);
	nbr = (long long)n;
	if (nbr == 0)
		res[0] = '0';
	else if (nbr < 0)
	{
		nbr = -nbr;
		res[0] = '-';
	}
	res[len] = '\0';
	while (nbr)
	{
		res[--len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (res);
}
