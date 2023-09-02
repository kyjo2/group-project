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

int	check_len(char **env)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (env[i])
	{
		if (env[i][0] == '_' && env[i][1] == '=')
			i++;
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

char	**copy_env(char **env, int env_len)
{
	char	**tmp;
	int		i;
	int		j;
	int		k;

	tmp = malloc(sizeof(char *) * env_len);
	i = 0;
	k = 0;
	while (env[i])
	{
		//printf("env[i][0] = %c env[i][1] = %c\n", env[i][0], env[i][1]);
		if (env[i][0] == '_' && env[i][1] == '=')
			i++;
		else
		{
			env_len = ft_strlen(env[i]);
			tmp[k] = malloc(sizeof(char) * env_len + 1);
			j = -1;
			while (env[i][++j])
				tmp[k][j] = env[i][j];
			tmp[k][j] = '\0';
			k++;
			i++;
		}
	}
	return (tmp);
}

// char	**sort_env(char **env)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;
// 	int		len;

// 	i = -1;
// 	len = check_len(env);
// 	printf("len = %d\n", len);
// 	while (++i < len)
// 	{
// 		j = i + 1;
// 		while (j < len)
// 		{
// 			//printf("env[i] = %s env[j] = %s\n", env[i], env[j]);	
// 			if (ft_strcmp(env[i], env[j]) > 0 && env[i] && env[j])
// 			{
// 				temp = env[i];
// 				env[i] = env[j];
// 				env[j] = temp;
// 			}
// 			j++;
// 		}
// 	}
// 	return (env);
// }

// void	declare_print(t_info *info)
// {
// 	char	**tmp_env;
// 	int	i;
// 	int	len;

// 	len = check_len(info->envp);
// 	tmp_env = copy_env(info->envp, len);
// 	tmp_env = sort_env(tmp_env);
// 	i = -1;
// 	while (tmp_env[++i])
// 		printf("%s\n", tmp_env[i]);
// 	free(tmp_env);
// }

// t_env	*sort_env(t_env	*env)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;
// 	int		len;

// 	i = -1;
// 	len = check_len(env);
// 	printf("len = %d\n", len);
// 	while (++i < len)
// 	{
// 		j = i + 1;
// 		while (j < len)
// 		{
// 			//printf("env[i] = %s env[j] = %s\n", env[i], env[j]);	
// 			if (ft_strcmp(env[i], env[j]) > 0 && env[i] && env[j])
// 			{
// 				temp = env[i];
// 				env[i] = env[j];
// 				env[j] = temp;
// 			}
// 			j++;
// 		}
// 	}
// 	return (env);
// }

void	declare_print(t_info *info)
{
	t_env	*tmp_env;

	tmp_env = info->envp_head;
	//tmp_env = sort_env(tmp_env);
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
	while (cmd[nlen + 1 + vlen] != '\0')
		vlen++;
	tmp->value = malloc(sizeof(char) * vlen + 1);
	if (!tmp->value)
		exit(1);
	i = -1;
	while (++i < vlen)
		tmp->value[i] = cmd[i + nlen + 1];
	tmp->value[i] = '\0';
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
			free(tmp.name);
			free(tmp.value);
		}
	}
	return (0);
}



// int	checkvalid(char *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if ((ft_isalnum(cmd[i]) == 0 && cmd[i] != '\''
// 				&& cmd[i] != '"' && cmd[i] != '_' && cmd)
// 			|| ft_isdigit(cmd[0]) == 1 || cmd[0] == '=')
// 		{
// 			puterror(cmd, "not a valid identifier");
// 			return (0);
// 		}
// 		i++;
// 		if (cmd[i] == '=')
// 			break ;
// 	}
// 	return (1);
// }

// void	export_print_2(char **env, int i, int j)
// {
// 	char	*temp;

// 	if (ft_strcmp(env[i], env[j]) > 0 && env[i] && env[j])
// 	{
// 		temp = env[i];
// 		env[i] = env[j];
// 		env[j] = temp;
// 	}
// }

// void	export_print(void)
// {
// 	int		len;
// 	char	**env;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	len = splitlen(g_data->env);
// 	env = array_dup();
// 	if (env == NULL)
// 		return ;
// 	while (i < len)
// 	{
// 		j = i + 1;
// 		while (++j < len)
// 			export_print_2(env, i, j);
// 		if (env[i])
// 			format_env(env[i]);
// 		i++;
// 	}
// }

// int	export(char **cmd)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 1;
// 	if (!cmd[1])
// 	{
// 		export_print();
// 		return (0);
// 	}
// 	while (cmd[i])
// 	{
// 		if (cmd[i][0] == '_' && cmd[i][1] == '=')
// 			return (0);
// 		if (!checkvalid(ft_ecrase_q(cmd[i])))
// 			return (1);
// 		tmp = ft_ecrase_q(cmd[i]);
// 		my_setenv(tmp);
// 		free(tmp);
// 		i++;
// 	}
// 	return (0);
// }