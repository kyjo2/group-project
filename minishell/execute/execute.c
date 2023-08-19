/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:09 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/19 13:54:07 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmd(t_list *list, t_env *env)
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
		return (other_cmd(list, env));
}

static int	syntax_error(t_list *cmd_head)
{
	t_list	*head;

	head = cmd_head;
	while (head)
	{
		if (head->exist_pipe && head->ac == 0)
		{
			g_exit_code = 258;
			return (1);
		}
		head = head->next;
	}
	return (0);
}

void	close_fd(t_list *list, pid_t pid)
{
	if (pid == 0)
	{
		if (list->pip[0] > 0)
			list->pip[0] = ft_close(list->pip[0]);
	}
	else
	{
		if (list->pip[1] > 0)
			list->pip[1] = ft_close(list->pip[1]);
	}
	return ;
}


void	yes_fork(t_list *list, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		redir(list);
		close_fd(list, pid);
		exit(execute_cmd(list, env));
	}
	else
		close_fd(list, pid);
	return ;
}

int	wait_process(void)
{
	int		status;
	int		ret;

	while (wait(&status) != -1)
	{
		if (WIFSIGNALED(status))
			ret = WTERMSIG(status);
		else
			ret = WEXITSTATUS(status);
	}
	return (ret);
}


int	execute(t_list *list, t_env *env)
{
	int	i;

	if (syntax_error(list))
	{
		perror("syntax error near unexpected token `|'");
		return (1);
	}
	if (!(list->next) && command_check(list))
	{
		in_out(list);
		redir(list);
		execute_cmd(list, env);
		return (1);
	}
	while (list)
	{
		in_out(list);
		pipe(list->pip);
		yes_fork(list, env);
		list = list->next;
	}
	wait_process();
	return (1);
}
