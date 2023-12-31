/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:10:10 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/26 00:37:28 by yul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	syntax_print(void)
{
	g_exit_code = 258;
	ft_putstr_fd("syntax error\n", 2);
	return (1);
}

static int	syntax_red(t_list *a, int i)
{
	if (!ft_strncmp(a->av[i], "<", 1) || !ft_strncmp(a->av[i], "<<", 2) \
		|| !ft_strncmp(a->av[i], ">", 1) || !ft_strncmp(a->av[i], ">>", 2))
	{
		if (i + 1 == a->ac)
			return (1);
		if (!ft_strcmp(a->av[i + 1], "<") \
		|| !ft_strcmp(a->av[i + 1], "<<") \
		|| !ft_strcmp(a->av[i + 1], ">") \
		|| !ft_strcmp(a->av[i + 1], ">>") \
		|| !ft_strncmp(a->av[i + 1], "(", 1) \
		|| !ft_strncmp(a->av[i + 1], ")", 1))
			return (1);
	}
	return (0);
}

int	syntax_error(t_list *cmd_head)
{
	t_list	*head;
	int		i;

	head = cmd_head;
	while (head)
	{
		i = 0;
		if (head->exist_pipe && (!head->next || head->ac == 0))
			return (syntax_print());
		while (i < head->ac)
		{
			if (syntax_red(head, i))
				return (syntax_print());
			i++;
		}
		if (!head->ac)
			return (1);
		head = head->next;
	}
	return (0);
}
