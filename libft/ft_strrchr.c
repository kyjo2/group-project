/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:58:38 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/19 12:49:19 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"	

char	*ft_strrchr(const char *str, int c)
{
	char	temp_c;
	char	*temp_str;
	char	*res;

	temp_str = (char *)str;
	temp_c = (char)c;
	res = NULL;
	while (*temp_str)
	{
		if (*temp_str == temp_c)
			res = temp_str;
		temp_str++;
	}
	if (temp_c == '\0')
		res = temp_str;
	return (res);
}
