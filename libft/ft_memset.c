/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:49:37 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/14 12:36:17 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp_b;
	unsigned char	temp_c;
	size_t			i;

	temp_b = b;
	temp_c = c;
	i = -1;
	while (++i < len)
	{
		*temp_b = temp_c;
		temp_b++;
	}
	return (b);
}
