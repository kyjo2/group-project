/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:27 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/19 16:12:20 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	declare_print(t_info *info)
{
	t_env	*tmp_env;

	tmp_env = info->envp_head;
	while (tmp_env)
	{
		if (tmp_env->name[0] == '_' && tmp_env->name[1] == '\0')
			tmp_env = tmp_env->next;
		else
		{
			if (tmp_env->have_equl == 0)
				printf("declare -x %s\n", tmp_env->name);
			else
			{
				if (tmp_env->value)
					printf("declare -x %s=\"%s\"\n", \
						tmp_env->name, tmp_env->value);
				else
					printf("declare -x %s=\"\"\n", tmp_env->name);
			}
			tmp_env = tmp_env->next;
		}
	}
}

void	pick_name_val2(t_env *tmp, char *cmd, int *nlen, int *vlen)
{
	int	i;

	while (cmd[*nlen + 1 + *vlen] != '\0')
		(*vlen)++;
	tmp->value = malloc(sizeof(char) * (*vlen) + 1);
	if (!tmp->value)
		exit(1);
	i = -1;
	while (++i < *vlen)
		tmp->value[i] = cmd[i + (*nlen) + 1];
	tmp->value[i] = '\0';
}

int	pick_name_val(t_env *tmp, char *cmd)
{
	int	nlen;
	int	vlen;
	int	i;

	nlen = 0;
	vlen = 0;
	while (cmd[nlen] != '=')
		nlen++;
	tmp->name = malloc(sizeof(char) * nlen + 1);
	if (!tmp->name)
		exit(1);
	i = -1;
	while (++i < nlen)
		tmp->name[i] = cmd[i];
	tmp->name[i] = '\0';
	if (cmd[nlen + 1] == '\0')
		return (0);
	pick_name_val2(tmp, cmd, &nlen, &vlen);
	return (1);
}

int	ft_export2(char **cmd, t_info *info, int i)
{
	t_env	tmp;
	int		return_flag;

	return_flag = 0;
	while (cmd[++i])
	{
		if ((cmd[i][0] != '_' && !ft_isalpha(cmd[i][0])) || !check_cmd(cmd[i]))
		{
			printf("bash: export: `%s': not a valid identifier\n", cmd[i]);
			return_flag = 1;
		}
		else if (ft_strrchr(cmd[i], '=') == 0)
			change_env_export(info, cmd[i], 0, 0);
		else
		{	
			if (pick_name_val(&tmp, cmd[i]) == 0)
				tmp.value = 0;
			change_env_export(info, tmp.name, tmp.value, 1);
			free_tmp(tmp);
		}
	}
	return (return_flag);
}

int	ft_export(char **cmd, t_info *info)
{
	if (!cmd[1])
	{
		declare_print(info);
		return (0);
	}
	return (ft_export2(cmd, info, 0));
}
