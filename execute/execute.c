/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 13:39:09 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/22 12:17:34 by kyjo             ###   ########.fr       */
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
		return (ft_exit(list->av));
	else
	{
		return (other_cmd(list, info));
	}
}

void	yes_fork(t_list *list, t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_perror("A fork error occurred", 1);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redir(list);
		close_fd(list, pid);
		if (list->infile == -1)
			exit(1);
		exit(execute_cmd(list, info));
	}
	signal(SIGINT, SIG_IGN);
	if (!list->next)
		info->last_pid = pid;
	if (list->ac != 0)
		if ((builtin_check(list) == 0 \
			&& command_check(list, info) == 127) \
			|| !ft_strncmp(list->av[0], "", 1))
			printf("minishell: %s: command not found!\n", list->av[0]);
	close_fd(list, pid);
	return ;
}

void	no_fork(t_list *list, t_info *info)
{
	int	in_fd;
	int	out_fd;

	in_fd = dup(STDIN_FILENO);
	out_fd = dup(STDOUT_FILENO);
	if (in_fd == -1 || out_fd == -1)
		ft_putstr_fd("A dup error occurred\n", 2);
	redir(list);
	g_exit_code = execute_cmd(list, info);
	if (dup2(in_fd, STDIN_FILENO) == -1 || dup2(out_fd, STDOUT_FILENO) == -1)
		ft_putstr_fd("A dup2 error occurred\n", 2);
}

static void	execute_fork(t_list *list, t_info *info)
{
	while (list)
	{
		if (pipe(list->pip) == -1)
			ft_putstr_fd("A pipe error occurred\n", 2);
		yes_fork(list, info);
		list = list->next;
		if (in_out(list, info))
			break ;
	}
}

void	execute(t_list *list, t_info *info)
{
	t_list	*head;

	head = list;
	signal(SIGINT, SIG_IGN);
	if (syntax_error(list))
		return (free_list(list));
	if (in_out(list, info))
		return (free_list(list));
	if (!(list->next) && builtin_check(list))
		no_fork(list, info);
	else
		execute_fork(list, info);
	free_in_list(head);
	free_list(head);
	wait_process(info);
}
