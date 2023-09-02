/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:05:19 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/14 12:48:55 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *str, int c)
{
	char	temp_c;
	char	*temp_str;

	temp_str = (char *)str;
	temp_c = (char)c;
	while (*temp_str)
	{
		if (*temp_str == temp_c)
			return (temp_str);
		temp_str++;
	}
	if (temp_c == '\0')
		return (temp_str);
	return (NULL);
}
