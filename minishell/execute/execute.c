/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:09 by kyjo              #+#    #+#             */
/*   Updated: 2023/07/26 08:59:54 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_check(t_list *list, int *i)
{
	if (ft_strncmp(list->av[*i], "<\0", 2))
		redir_one();
	if (ft_strncmp(list->av[*i], ">\0", 2))
		redir_two();
	if (ft_strncmp(list->av[*i], "<<\0", 2))
		redir_three();
	if (ft_strncmp(list->av[*i], "<<\0", 2))
		redir_four();
}
char	*get_cmd(char **path, char *cmd)
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

char	*find_value(t_env *env, char *name)
{
	t_env	*head;

	head = env;
	while (head && ft_strncmp(name, head->name, ft_strlen(head->name)))
		head = head->next;
	if (!head)
		return (NULL);
	return (head->value);
}

int	other_cmd(t_list *list, t_env *env)
{
	list->cmd = get_cmd(find_value(env, "PATH"), list->av[0]);
	if (!list->cmd)
		exit(127);
	evecve(list->cmd, list->av, list->envp);
}

int	command_check(t_list *list, t_env *env, int *i)
{
	if (ft_strncmp(list->av[*i], "echo\0", 5))
		return (ft_echo());
	else if (ft_strncmp(list->av[*i], "cd\0", 3))
		return (ft_cd());
	else if (ft_strncmp(list->av[*i], "pwd\0", 4))
		return (ft_pwd());
	else if (ft_strncmp(list->av[*i], "export\0", 7))
		return (ft_export());
	else if (ft_strncmp(list->av[*i], "unset\0", 6))
		return (ft_unset());
	else if (ft_strncmp(list->av[*i], "env\0", 4))
		return (ft_env());
	else if (ft_strncmp(list->av[*i], "exit\0", 5))
		return (ft_exit());
	else
		return (other_cmd(list, env));
}

int	check_syntax(t_list *list, t_env *env)
{
	t_list	*head;
	int	i;

	head = list;
	while (head)
	{
		i = 0;
		while (head->av[i])
		{
			redir_check(head, &i);
			command_check(head, env, &i);
			envir_check(head->av[i]);
			i++;
		}
		head = head->next;
	}
}

int	execute(t_list *list, t_env *env)
{
	check_syntax(list, env);
}
