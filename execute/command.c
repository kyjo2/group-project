/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:53:42 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/15 00:43:31 by yul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cmd(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*tmp;

	fd = access(cmd, X_OK);
	if (!fd)
		return (ft_strdup(cmd));
	path_cmd = ft_strjoin("/", cmd);
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

char	**find_path(t_env *head)
{
	char	*path;

	while (head && ft_strcmp("PATH", head->name))
		head = head->next;
	if (!head)
		return (NULL);
	path = head->value;
	return (ft_split(path, ':'));
}

int	other_cmd(t_list *list, t_info *info)
{
	char	**path;

	path = find_path(info->envp_head);
	if (!path)
		return (127);
	list->cmd = get_cmd(path, list->av[0]);
	deep_free(path);
	if (!list->cmd)
		return (127);
	return (execve(list->cmd, list->av, list->envp));
}

int	builtin_check(t_list *list)
{
	if (!ft_strcmp(list->av[0], "cd"))
		return (1);
	else if (!ft_strcmp(list->av[0], "export"))
		return (1);
	else if (!ft_strcmp(list->av[0], "unset"))
		return (1);
	else if (!ft_strcmp(list->av[0], "exit"))
		return (1);
	else
		return (0);
}

int	command_check(t_list *list, t_info *info)
{
	char	**temp;

	temp = find_path(info->envp_head);
	if (!temp)
		return (127);
	list->cmd = get_cmd(temp, list->av[0]);
	deep_free(temp);
	if (!list->cmd)
		return (127);
	free(list->cmd);
	list->cmd = NULL;
	return (0);
}
