/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:09 by kyjo              #+#    #+#             */
/*   Updated: 2023/07/24 15:55:44 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_check(t_info *info, int *i)
{
	if (ft_strncmp(info->av[*i], "<\0", 2))
		redir_one();
	if (ft_strncmp(info->av[*i], ">\0", 2))
		redir_two();
	if (ft_strncmp(info->av[*i], "<<\0", 2))
		redir_three();
	if (ft_strncmp(info->av[*i], "<<\0", 2))
		redir_four();
}
char	*other_cmd(char **path, char *cmd)
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

int	command_check(t_info *info, int *i)
{
	if (ft_strncmp(info->av[*i], "echo\0", 5))
		ft_echo();
	else if (ft_strncmp(info->av[*i], "cd\0", 3))
		ft_cd();
	else if (ft_strncmp(info->av[*i], "pwd\0", 4))
		ft_pwd();
	else if (ft_strncmp(info->av[*i], "export\0", 7))
		ft_export();
	else if (ft_strncmp(info->av[*i], "unset\0", 6))
		ft_unset();
	else if (ft_strncmp(info->av[*i], "env\0", 4))
		ft_env();
	else if (ft_strncmp(info->av[*i], "exit\0", 5))
		ft_exit();
}

int	check_syntax(t_info *info)
{
	int	i;

	while (info->next)
	{
		i = 0;
		while (info->av[i])
		{
			redir_check(info, &i);
			command_check(info, &i);
			envir_check(info->av[i]);
			i++;
		}
		info = info->next;
	}
}

int	execute(t_info *info)
{
	check_syntax(info);
}
