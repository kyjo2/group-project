/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:36:54 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/17 15:45:14 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*temp_s1;
	size_t	i;

	temp_s1 = (char *)s1;
	i = 0;
	if (*s2 == '\0')
		return (temp_s1);
	while (i < n && s1[i])
	{
		if (ft_strncmp(&s1[i], s2, ft_strlen(s2)) == 0)
		{
			if (i + ft_strlen(s2) > n)
				return (NULL);
			return (temp_s1);
		}
		temp_s1++;
		i++;
	}
	return (NULL);
}
