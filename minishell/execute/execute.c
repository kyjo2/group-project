/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:09 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/26 14:02:18 by yul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmd(t_list *list)
{
	if (!ft_strncmp(list->av[0], "echo", 4))
		return (ft_echo(list->av[1]));
	else if (!ft_strncmp(list->av[0], "cd", 2))
		return (ft_cd());
	else if (!ft_strncmp(list->av[0], "pwd", 3))
		return (ft_pwd(list->ac));
	else if (!ft_strncmp(list->av[0], "export", 6))
		return (ft_export());
	else if (!ft_strncmp(list->av[0], "unset", 5))
		return (ft_unset());
	else if (!ft_strncmp(list->av[0], "env", 3))
		return (ft_env(list->envp));
	else if (!ft_strncmp(list->av[0], "exit", 4))
		return (ft_exit());
	else
		return (other_cmd(list));
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
			list->pip[0] = close(list->pip[0]);
	}
	else
	{
		if (list->pip[1] > 0)
			list->pip[1] = close(list->pip[1]);
	}
	return ;
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

void	free_list(t_list *head)
{
	while (head)
	{
		if (head->pip[READ] > 0)
			close(head->pip[READ]);
		if (head->infile > 0)
			close(head->infile);
		if (head->outfile > 0)
			close(head->outfile);
		if (head->cmd)
			free(head->cmd);
		head = head->next;
	}
}

int	execute(t_list *list)
{
	t_list	*head;

	head = list;
	if (syntax_error(list))
	{
		perror("syntax error near unexpected token `|'");
		return (1);
	}
	if (!(list->next) && command_check(list))
	{
		in_out(list);
		redir(list);
		execute_cmd(list);
		return (1);
	}
	while (list)
	{
		in_out(list);
		pipe(list->pip);
		yes_fork(list);
		list = list->next;
		in_out(list);
	}
	wait_process();
	free_list(head);
	return (1);
}
