/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:19:27 by junggkim          #+#    #+#             */
/*   Updated: 2023/08/21 21:15:17 by yul              ###   ########.fr       */
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
					printf("declare -x %s=\"%s\"\n", tmp_env->name, tmp_env->value);
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

int		pick_name_val(t_env *tmp, char *cmd)
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

int		check_cmd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0' && cmd[i] != '=')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	free_tmp(t_env tmp)
{
	free(tmp.name);
	free(tmp.value);
}

// export a                            #key값만 생성
// export b=                           #value에 아무 값 없음
// export c=hello          
// export d="oh      my          god"  #echo출력과 export출력 다름
// export e=elephant f=flower
// export 1e=23                        #ㄴ숫자는 환경변수 추가안된다
// export b=acd 에서 export b 는 b가 따로 선언이 되지 않는다. 
int	ft_export(char **cmd, t_info *info)
{
	int		i;
	t_env	tmp;

	if (!cmd[1])
	{
		declare_print(info);
		return (0);
	}
	i = 0;
	while (cmd[++i])
	{
		if ((cmd[i][0] != '_' && !ft_isalpha(cmd[i][0])) || !check_cmd(cmd[i])) //
			printf("bash: export: `%s': not a valid identifier\n", cmd[i]);
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
	return (0);
}

