/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:18:52 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/09 13:48:05 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_env(char *path, t_info *info)
{
	t_env	*tmp;

	tmp = info->envp_head;
	while (tmp)
	{
		if (!ft_strcmp(path, tmp->name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

int	dir(char *path, t_info *info)
{
	char	*tmp;
	int		result;

	tmp = NULL;
	if (!ft_strcmp("~", path))
		tmp = ft_strdup(check_env("HOME", info));
	else if (!ft_strcmp("-", path))
	{
		if ((check_oldpwd("OLDPWD", info)))
			return (1);
		else
			tmp = ft_strdup(check_env("OLDPWD", info));
	}
	else
		tmp = ft_strdup(path);
	if (!tmp)
		exit(1);
	result = chdir(tmp);
	free(tmp);
	return (result);
}

int	ft_cd(char **cmd, t_info *info)
{
	char	pwd[4096];
	int		tmp;

	if (!cmd[1])
		dir("~", info);
	tmp = dir(cmd[1], info);
	if (tmp == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", cmd[1]);
		return (1);
	}
	else if (tmp == 1)
	{
		printf("bash: cd: OLDPWD not set\n");
		return (1);
	}
	else
	{
		getcwd(pwd, 4096);
		change_env_export(info, "OLDPWD", check_env("PWD", info), 1);
		change_env_export(info, "PWD", pwd, 1);
	}
	return (0);
}
