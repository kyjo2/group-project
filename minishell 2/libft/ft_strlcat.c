/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:10:43 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/17 16:41:01 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (len == 0)
		return (src_len);
	if (len <= dst_len)
		return (src_len + len);
	src_len = dst_len + src_len;
	while (*src && dst_len < len - 1)
	{
		dest[dst_len] = *src;
		src++;
		dst_len++;
	}
	dest[dst_len] = '\0';
	return (src_len);
}
