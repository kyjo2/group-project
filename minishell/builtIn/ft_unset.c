/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:39 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/04 20:44:45 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_env(t_info *info, char *name)
{
	t_env	*tmp;
	t_env	*pre;

	tmp = info->envp_head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			pre->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			break ;
		}
		else
			pre = tmp;
		tmp = tmp->next;
	}
}

int		unset_check_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
// unset a
// unset b c
// unset abcdef
int	ft_unset(char **cmd, t_info *info)
{
	int		i;

	if (!cmd[1])
		return (0);
	i = 0;
	while (cmd[++i])
	{
		if ((cmd[i][0] != '_' && !ft_isalpha(cmd[i][0])) || !unset_check_cmd(cmd[i]))  // 이부분 다시 생각해보기 
		{
			printf("bash: unset: `%s': not a valid identifier\n", cmd[i]);
			return (1);
		}
		else
			delete_env(info, cmd[i]);
	}
	return (0);
}
