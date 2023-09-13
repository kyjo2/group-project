/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:44:58 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/13 21:15:37 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*cd_find_env(t_info *info, char *name)
{
	t_env	*tmp;

	tmp = info->envp_head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*create_env(char *name, char *value, int have_equl)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		exit(1);
	new_env->name = ft_strdup(name);
	if (have_equl == 0)
		new_env->value = NULL;
	else
	{
		if (value)
			new_env->value = ft_strdup(value);
		else
			new_env->value = ft_strdup("");
	}
	new_env->have_equl = have_equl;
	new_env->next = NULL;
	return (new_env);
}

void	add_env(t_env **envp_head, char *name, char *value, int have_equl)
{
	t_env	*tmp;

	if (*envp_head == NULL)
		*envp_head = create_env(name, value, have_equl);
	else
	{
		tmp = *envp_head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = create_env(name, value, have_equl);
	}
}

void	change_env_export(t_info *info, char *name, char *value, int have_equl)
{
	t_env	*tmp;

	tmp = cd_find_env(info, name);
	if (tmp == NULL)
		add_env(&info->envp_head, name, value, have_equl);
	else
	{
		if (tmp->value && have_equl == 1)
		{
			free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = ft_strdup("");
		}
		else
		{
			if (value)
				tmp->value = new_strdup(value, tmp);
			else if (have_equl)
				tmp->value = new_strdup("", tmp);
		}
	}
}

int	check_oldpwd(char *path, t_info *info)
{
	t_env	*tmp;

	tmp = info->envp_head;
	while (tmp)
	{
		if (!ft_strcmp(path, tmp->name))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
