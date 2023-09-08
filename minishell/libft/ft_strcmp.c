/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:18:24 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/20 12:18:35 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)        // libft 에 있는거 고쳐야함 $US 랑 $USER이랑 같다고 보기 떄문에 밑에 처럼 고쳐야함
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	if (s1[0] == '\0' && s2[0] == '\0')
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	return (0);
}
