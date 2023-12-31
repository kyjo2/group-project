/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:44:29 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/13 23:13:06 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*temp_s;
	size_t	size;
	size_t	i;

	temp_s = NULL;
	size = ft_strlen(s);
	i = 0;
	temp_s = malloc(size + 1);
	if (temp_s == NULL)
		exit(1);
	while (s[i])
	{
		temp_s[i] = s[i];
		i++;
	}
	temp_s[i] = '\0';
	return (temp_s);
}
