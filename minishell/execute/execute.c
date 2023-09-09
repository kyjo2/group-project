/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:09 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/09 16:07:12 by yul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_cmd(t_list *list, t_info *info)
{
	if (list->ac == 0)
		return (0);
	else if (!ft_strcmp(list->av[0], "echo"))
		return (ft_echo(list->av));
	else if (!ft_strcmp(list->av[0], "cd"))
		return (ft_cd(list->av, info));
	else if (!ft_strcmp(list->av[0], "pwd"))
		return (ft_pwd(list->outfile, info));
	else if (!ft_strcmp(list->av[0], "export"))
		return (ft_export(list->av, info));
	else if (!ft_strcmp(list->av[0], "unset"))
		return (ft_unset(list->av, info));
	else if (!ft_strcmp(list->av[0], "env"))
		return (ft_env(info->envp_head));
	else if (!ft_strcmp(list->av[0], "exit"))
		return (ft_exit(list->av, list->exist_pipe));
	else
	{
		return (other_cmd(list));
	}
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
		if (list->infile == -1)
			exit(1);
		exit(execute_cmd(list, info));
	}
	else if (pid != 0)
	{
		signal(SIGINT, SIG_IGN);
		if (!list->next)
			info->last_pid = pid;
		if (list->ac != 0)
			if (command_check(list) == 127 || !ft_strncmp(list->av[0], "", 1))
				printf("minishell: %s: command not found\n", list->av[0]);
		close_fd(list, pid);
	}
	return ;
}

static void	execute_fork(t_list *list, t_info *info)
{
	while (list)
	{
		pipe(list->pip);
		yes_fork(list, info);
		list = list->next;
		in_out(list);
	}
}

void	execute(t_list *list, t_info *info)
{
	t_list	*head;

	head = list;
	if (syntax_error(list))
		return ;
	in_out(list);
	if (!(list->next) && builtin_check(list) \
		&& list->infile <= 0 && list->outfile <= 0)
	{
		redir(list);
		if (list->infile == -1)
			g_exit_code = 1;
		else
			g_exit_code = execute_cmd(list, info);
	}
	else
		execute_fork(list, info);
	unlink_tmp_file();
	free_in_list(head);
	free_list(head);
	wait_process(info);
}
