/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:53:42 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/07 13:53:54 by yul              ###   ########.fr       */
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

static char	**find_path(char **ev)
{
	char	*path;

	while (*ev && ft_strncmp("PATH=", *ev, 5))
		ev++;
	if (*ev == NULL)
		return (NULL);
	path = *ev + 5;
	return (ft_split(path, ':'));
}

int	other_cmd(t_list *list)
{
	list->cmd = get_cmd(find_path(list->envp), list->av[0]);
	if (!list->cmd)
		return (127);
	return (execve(list->cmd, list->av, list->envp));
}

int	command_check(t_list *list)
{
	if (!ft_strncmp(list->av[0], "echo\0", 5))
		return (1);
	else if (!ft_strncmp(list->av[0], "cd\0", 3))
		return (1);
	else if (!ft_strncmp(list->av[0], "pwd\0", 4))
		return (1);
	else if (!ft_strncmp(list->av[0], "export\0", 7))
		return (1);
	else if (!ft_strncmp(list->av[0], "unset\0", 6))
		return (1);
	else if (!ft_strncmp(list->av[0], "env\0", 4))
		return (1);
	else if (!ft_strncmp(list->av[0], "exit\0", 5))
		return (1);
	else
	{
		list->cmd = get_cmd(find_path(list->envp), list->av[0]);
		if (!list->cmd)
			return (127);
	}
	return (0);
}