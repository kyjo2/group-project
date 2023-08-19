/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:47:49 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/13 18:52:36 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = (ft_strlen(s) - start);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
