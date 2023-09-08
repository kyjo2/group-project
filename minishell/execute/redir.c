/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:32:03 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/10 13:12:18 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_set(t_list *list)
{
	if (list->prev)
		dup2(list->prev->pip[READ], STDIN_FILENO);
	if (list->exist_pipe)
    	dup2(list->pip[WRITE], STDOUT_FILENO);
}

static void	redir_infile(t_list *list)
{
	if (list->infile > 0)
	    dup2(list->infile, STDIN_FILENO);
}

static void	redir_outfile(t_list *list)
{
	if (list->outfile > 0)
	    dup2(list->outfile, STDOUT_FILENO);
}

void	redir(t_list *list)
{
	pipe_set(list);
	redir_infile(list);
	redir_outfile(list);
	return ;
}
