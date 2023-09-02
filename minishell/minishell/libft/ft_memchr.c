/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:49:01 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/14 16:58:34 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *arr, int c, size_t n)
{
	unsigned char	*temp_arr;
	unsigned char	temp_c;
	size_t			i;

	temp_arr = (unsigned char *)arr;
	temp_c = c;
	i = 0;
	while (i < n)
	{
		if (*temp_arr == temp_c)
			return (temp_arr);
		temp_arr++;
		i++;
	}
	return (NULL);
}
