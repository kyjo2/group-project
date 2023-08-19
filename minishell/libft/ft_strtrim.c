/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:48:38 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/19 12:44:34 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	s1_len;

	if (s1 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (i == s1_len)
		return (ft_strdup(""));
	while (--s1_len)
		if (ft_strchr(set, s1[s1_len]) == NULL)
			break ;
	res = ft_substr(s1, i, (s1_len - i + 1));
	return (res);
}
