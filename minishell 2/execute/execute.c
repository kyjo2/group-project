/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:09 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/07 14:06:01 by yul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmd(t_list *list, t_info *info)
{
	if (!ft_strncmp(list->av[0], "echo\0", 5))
		return (ft_echo(list->av));
	else if (!ft_strncmp(list->av[0], "cd\0", 3))
		return (ft_cd(list->av, info));
	else if (!ft_strncmp(list->av[0], "pwd\0", 4))
		return (ft_pwd(list->outfile));
	else if (!ft_strncmp(list->av[0], "export\0", 7))
		return (ft_export(list->av, info));
	else if (!ft_strncmp(list->av[0], "unset\0", 6))
		return (ft_unset(list->av, info));
	else if (!ft_strncmp(list->av[0], "env\0", 4))
		return (ft_env(info->envp_head));
	else if (!ft_strncmp(list->av[0], "exit\0", 5))
		return (ft_exit(list->av));
	else
		return (other_cmd(list));
}

static int	syntax_error(t_list *cmd_head)
{
	t_list	*head;

	head = cmd_head;
	while (head)
	{
		if (head->exist_pipe && (!head->next || head->ac == 0))
		{
			g_exit_code = 258;
			perror("syntax error near unexpected token `|'");
			return (1);
		}
		if (!head->ac)
			return (1);
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


void	yes_fork(t_list *list, t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redir(list);
		close_fd(list, pid);
		exit(execute_cmd(list, info));
	}
	else
	{
		if (!list->next)
			info->last_pid = pid;
		if (command_check(list) == 127 || !ft_strncmp(list->av[0], "", 1))
			printf("minishell: %s: command not found\n", list->av[0]);
		close_fd(list, pid);
	}
	return ;
}

void	wait_process(t_info *info)
{
	pid_t	temp;
	int		status;
	int		ret;

	temp = wait(&status);
	while (temp != -1)
	{
		if (WIFSIGNALED(status))
			ret = WTERMSIG(status);
		else
			ret = WEXITSTATUS(status);
		if (ret == 2)
			ret = 130;
		if (temp == info->last_pid)
			g_exit_code = ret;
		temp = wait(&status);
	}
}

void	free_list(t_list *head)
{
	while (head)
	{
		if (head->pip[READ] > 0)
			close(head->pip[READ]);
		if (head->pip[WRITE] > 0)
			close(head->pip[WRITE]);
		if (head->infile > 0)
			close(head->infile);
		if (head->outfile > 0)
			close(head->outfile);
		if (head->cmd)
			free(head->cmd);
		head = head->next;
	}
}

int	execute(t_list *list, t_info *info)
{
	t_list	*head;
	//int		i;

	// i = 0;
	// while (list->av[i])
	// 	printf("cmd = %s\n", list->av[i++]);
	head = list;
	if (syntax_error(list))
		return (1);
	if (!(list->next) && command_check(list) == 1)
	{
		in_out(list);
		redir(list);
		g_exit_code = execute_cmd(list, info);
	}
	else
	{
		while (list)
		{
			pipe(list->pip);
			in_out(list);
			yes_fork(list, info);
			list = list->next;
		}
	}
	free_list(head);
	wait_process(info);
	return (1);
}
