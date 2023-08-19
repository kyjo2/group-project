/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:34:17 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/14 13:18:08 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*temp_s1;
	unsigned char	*temp_s2;

	temp_s1 = (unsigned char *)s1;
	temp_s2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*temp_s1 == *temp_s2)
		{
			temp_s1++;
			temp_s2++;
			n--;
		}
		else
			return (*temp_s1 - *temp_s2);
		if ((*temp_s1 == '\0') && (*temp_s2 == '\0'))
			return (0);
	}
	return (0);
}
