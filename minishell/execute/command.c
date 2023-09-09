/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:53:42 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/08 19:37:01 by yul              ###   ########.fr       */
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
		return (cmd);
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

char	**find_path(char **envp)
{
	char	*path;

	while (*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (!*envp)
		return (NULL);
	path = *envp + 5;
	return (ft_split(path, ':'));
}

int	other_cmd(t_list *list)
{
	if (find_path(list->envp) == NULL)
		return (127);
	list->cmd = get_cmd(find_path(list->envp), list->av[0]);
	if (!list->cmd)
		return (127);
	return (execve(list->cmd, list->av, list->envp));
}

int	command_check(t_list *list)
{
	if (!ft_strcmp(list->av[0], "echo"))
		return (1);
	else if (!ft_strcmp(list->av[0], "cd"))
		return (1);
	else if (!ft_strcmp(list->av[0], "pwd"))
		return (1);
	else if (!ft_strcmp(list->av[0], "export"))
		return (1);
	else if (!ft_strcmp(list->av[0], "unset"))
		return (1);
	else if (!ft_strcmp(list->av[0], "env"))
		return (1);
	else if (!ft_strcmp(list->av[0], "exit"))
		return (1);
	else
	{
		if (!find_path(list->envp))
			return (127);
		list->cmd = get_cmd(find_path(list->envp), list->av[0]);
		if (!list->cmd)
			return (127);
	}
	return (0);
}