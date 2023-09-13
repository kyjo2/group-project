/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:55:44 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/13 21:14:31 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	free_tmp(t_env tmp)
{
	free(tmp.name);
	free(tmp.value);
}

char	*new_strdup(const char *s, t_env *tmp)
{
	char	*temp_s;
	size_t	size;
	size_t	i;

	tmp->have_equl = 1;
	temp_s = NULL;
	size = ft_strlen(s);
	i = 0;
	temp_s = malloc(size + 1);
	if (temp_s == NULL)
		return (NULL);
	while (s[i])
	{
		temp_s[i] = s[i];
		i++;
	}
	temp_s[i] = '\0';
	return (temp_s);
}
