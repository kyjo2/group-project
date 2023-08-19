/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:51:38 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/19 10:37:27 by kyjo             ###   ########.fr       */
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

char	*get_cmd(char **path, char *list)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*tmp;

	fd = access(list, X_OK);
	if (!fd)
		return (list);
	path_cmd = ft_strjoin("/", list);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], path_cmd);
		fd = access(tmp, X_OK);
		if (!fd)
		{
			free(path_cmd);
			return (tmp);
		}
		close(fd);
		free(tmp);
		i++;
	}
	free(path_cmd);
	return (NULL);
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

int	command_check(t_list *list)
{
	if (ft_strncmp(list->av[0], "echo\0", 5))
		return (1);
	else if (ft_strncmp(list->av[0], "cd\0", 3))
		return (1);
	else if (ft_strncmp(list->av[0], "pwd\0", 4))
		return (1);
	else if (ft_strncmp(list->av[0], "export\0", 7))
		return (1);
	else if (ft_strncmp(list->av[0], "unset\0", 6))
		return (1);
	else if (ft_strncmp(list->av[0], "env\0", 4))
		return (1);
	else if (ft_strncmp(list->av[0], "exit\0", 5))
		return (1);
	else
		return (0);
}