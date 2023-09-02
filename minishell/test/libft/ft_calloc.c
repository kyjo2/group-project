/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 21:27:11 by yul               #+#    #+#             */
/*   Updated: 2022/11/17 16:49:41 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	char	*result;
	size_t	length;

	result = NULL;
	length = size * n;
	if (length == 0)
	{
		result = malloc(0);
		return (result);
	}
	if (length / n != size)
		return (NULL);
	result = malloc(length);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, length);
	return (result);
}
