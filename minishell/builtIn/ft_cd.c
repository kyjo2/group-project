/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:18:52 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/04 11:18:00 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*cd_find_env(t_info *info, char *name)
{
	t_env	*tmp;

	tmp = info->envp_head;
	while (tmp)
	{
		// printf("%s\n", tmp->name);
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
			new_env->value = ft_strdup("");   // ft_stdup("")의미 다시 !! 빈문자열인데 메모리할당이 되지 않는다
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
		if (tmp->value && have_equl == 1)    // a=abc 이렇게 있는경우
		{
			free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = 0;
		}
		else             // a=  || a 일경우
		{
			if (value)       	
				tmp->value = ft_strdup(value);
			tmp->have_equl = 1;
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
	return ("");   // 여기 리턴값을 설정잘해보자
}

int	dir(char *path, t_info *info)
{
	char	*tmp;
	int		result;

	tmp = NULL;
	if (!ft_strcmp("~", path))
		tmp = ft_strdup(check_env("HOME",info));
	else if (!ft_strcmp("-", path))
	{
		if ((check_oldpwd("OLDPWD", info)))
			return (1);
		else
			tmp = ft_strdup(check_env("OLDPWD",info));
	}
	else
		tmp = ft_strdup(path);
	if (!tmp)
		exit(1);
	result = chdir(tmp);
	free(tmp);
	return (result);
}

void	printf_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
        tmp = tmp->next;
    }
}

//왜 OLDPWD가 미리 생성되어 있는것인가?
// cd ..
// cd .
// cd /Users/su
//getcwd, chdir
int	ft_cd(char **cmd, t_info *info)                 // 에러 값일때 return (1)  정상종료면 return (0);
{
	char	pwd[4096];

	if (!cmd[1])
		dir("~", info);
	else if(dir(cmd[1], info) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", cmd[1]);
		return (1);
	}
	else if (dir(cmd[1], info) == 1)
	{
		printf("bash: cd: OLDPWD not set\n");
		return (1);
	}
	else
	{
		getcwd(pwd, 4096);
 		change_env_export(info, "OLDPWD", check_env("PWD", info), 1);
 		change_env_export(info, "PWD", pwd, 1);
		//printf_env(info->envp_head);
	}
	return (0);
}


