/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:51:38 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/09 14:00:21 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->next = NULL;
	return (new);
}

t_env	*find_env(char **ev)
{
	t_env	*head;
	t_env	*temp;
	t_env	*new;
	int		i;

	new = new_env();
	head = new;
	while (*ev)
	{
		i = 0;
		while ((*ev)[i] != '=')
			i++;
		new->name = malloc(sizeof(char) * (i + 1));
		ft_strlcpy(new->name, *ev, i + 1);
		new->value = ft_strdup(&(*ev)[i + 1]);
		new->have_equl = 1;
		ev++;
		if (*ev)
		{
			temp = new_env();
			new->next = temp;
			new = temp;
		}
	}
	return (head);
}

char	*find_value(t_env *env, char *name)
{
	t_env	*head;

	head = env;
	while (head && ft_strncmp(name, head->name, ft_strlen(head->name)))
		head = head->next;
	if (!head)
		return (NULL);
	return (head->value);
}

void	free_list(t_list *head)
{
	t_list	*current;
	t_list	*temp;

	current = head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

void	free_env(t_env *head)
{
	t_env	*current;
	t_env	*temp;

	current = head;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}
