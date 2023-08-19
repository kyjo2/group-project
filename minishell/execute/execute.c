/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:09 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/19 10:23:53 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd(char **path, char *list)
{
	int		i;
	int		fd;
	char	*path_cmd;
	char	*tmp;

	fd = access(list, X_OK);
	if (!fd)
		return (list);
	path_cmd = ft_strjoin("/", list);
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

int	command_check(t_list *list)
{
	if (ft_strncmp(list->av[0], "echo\0", 5))
		return (ft_echo());
	else if (ft_strncmp(list->av[0], "cd\0", 3))
		return (ft_cd());
	else if (ft_strncmp(list->av[0], "pwd\0", 4))
		return (ft_pwd());
	else if (ft_strncmp(list->av[0], "export\0", 7))
		return (ft_export());
	else if (ft_strncmp(list->av[0], "unset\0", 6))
		return (ft_unset());
	else if (ft_strncmp(list->av[0], "env\0", 4))
		return (ft_env());
	else if (ft_strncmp(list->av[0], "exit\0", 5))
		return (ft_exit());
	else
		return (-50);
}

int	alone_pipe(t_list *list)
{
	if (list->exist_pipe && list->ac == 0)
	{
		exit(258);
		return (1);
	}
	return (0);
}

static int	syntax_error(t_list *cmd_head)
{
	t_list	*head;

	head = cmd_head;
	if (alone_pipe(head))
		return (1);
	while (head)
		head = head->next;
	return (0);
}


void	yes_fork(t_list *list)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		redir(list);
		close_fd(list, pid);
		exit(execute_cmd(list));
	}
	else
		close_fd(list, pid);
	return ;
}

int	wait_process(void)
{
	int		status;
	int		signo;

	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
			signo = WTERMSIG(status);
		else
			signo = WEXITSTATUS(status);
	}
	return (signo);
}


int	execute(t_list *list, t_env *env)
{
	int	i;

	if (syntax_error(list))
		exit(127);
	if (!(list->next) && command_check(list) != -50)
	{
		in_out(list);
		redir(list);
		no_fork();
	}
	else
	{
		while (list)
		{
			pipe(list->pip);
			in_out(list);
			yes_fork(list);
			list = list->next;
		}
		wait_process();
	}
	return (1);
}
