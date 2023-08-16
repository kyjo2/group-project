/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:51:38 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/12 18:44:45 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**find_path(char **ev)
{
	char	*path;

	while (*ev && ft_strncmp("PATH=", *ev, 5))
		ev++;
	if (*ev == NULL)
		return (NULL);
	path = *ev + 5;
	return (ft_split(path, ':'));
}

t_env	*find_env(char **ev)
{
	t_env	*head;
	t_env	*temp;
	t_env	*new;
	int		i;

	new = malloc(sizeof(t_env));
	new->next = NULL;
	head = new;
	while (*ev)
	{
		i = 0;
		while ((*ev)[i] != '=')
			i++;
		new->name = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(new->name, *ev, i + 1);
		*ev += (i + 1);
		new->value = ft_strdup(*ev);
		ev++;
		if (*ev)
		{
			temp = malloc(sizeof(t_env));
			temp->next = NULL;
			new->next = temp;
			new = temp;
		}
	}
	return (head);
}
