/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:21:19 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/09 16:37:48 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_doubleq(char s1)
{
	if (s1 != '_' && (s1 < 'A' || s1 > 'Z') && (s1 < '0' || s1 > '9')
		&& (s1 < 'a' || s1 > 'z') && s1 != '?' && s1 != '$')
		return (0);
	return (1);
}

int	change_check(char **line, int *i, int doubleq)
{
	if (((*line)[(*i) + 1] == '\0' || (*line)[(*i) + 1] == ' ') && doubleq == 0)
		return (1);
	else if (((*line)[(*i) + 1] == '\"' || (*line)[(*i) + 1] == ' '
				|| check_doubleq((*line)[(*i) + 1]) == 0) && doubleq == 1)
		return (1);
	else if ((*line)[(*i) + 1] == '$')
	{
		(*line)[(*i)] = '4';
		(*line)[(*i) + 1] = '2';
		return (1);
	}
	return (0);
}
