/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:53:42 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/22 13:05:29 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cmd(char **path, char *cmd)
{
	char	*path_cmd;
	char	*tmp;

	if (!check_file(cmd))
		return (ft_strdup(cmd));
	if (!path)
		return (NULL);
	path_cmd = ft_strjoin("/", cmd);
	while (*path)
	{
		tmp = ft_strjoin(*path, path_cmd);
		if (!check_file(tmp))
		{
			free(path_cmd);
			return (tmp);
		}
		free(tmp);
		path++;
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
	list->cmd = get_cmd(path, list->av[0]);
	if (path)
		deep_free(path);
	if (!list->cmd)
		return (127);
	if (list->infile == -1 || list->outfile == -1)
		return (1);
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
	else if (!ft_strcmp(list->av[0], "echo"))
		return (1);
	else if (!ft_strcmp(list->av[0], "env"))
		return (1);
	else if (!ft_strcmp(list->av[0], "pwd"))
		return (1);
	else
		return (0);
}

int	command_check(t_list *list, t_info *info)
{
	char	**temp;

	temp = find_path(info->envp_head);
	list->cmd = get_cmd(temp, list->av[0]);
	if (temp)
		deep_free(temp);
	if (!list->cmd)
		return (127);
	free(list->cmd);
	list->cmd = NULL;
	return (0);
}
