/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:50:00 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/19 12:47:49 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	char_cnt(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		while (*s != c && *s != '\0')
			s++;
		cnt++;
	}
	return (cnt);
}

static void	*is_free(char **s, size_t str_index)
{
	size_t	i;

	i = 0;
	while (i < str_index)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	**set_worddup(char const *s, char c, char **result)
{
	size_t	length;
	size_t	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		length = 0;
		while (s[length] && s[length] != c)
			length++;
		result[i] = (char *)malloc(sizeof(char) * (length + 1));
		if (result[i] == NULL)
			return (is_free(result, i));
		ft_strlcpy(result[i], s, length + 1);
		s += length;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	size_t	cnt;
	char	**result;

	result = NULL;
	if (!s)
		return (NULL);
	cnt = char_cnt(s, c);
	result = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (result == NULL)
		return (NULL);
	result = set_worddup(s, c, result);
	return (result);
}
