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

void	pipe_set(t_list *list)
{
	if (list->prev)
		dup2(list->prev->pip[0], 0);
	if (list->exist_pipe)
    	dup2(list->pip[1], 1);
}

void	redir_infile(t_list *list)
{
	if (list->infile > 0)
	    dup2(list->infile, 0);
}

void	redir_outfile(t_list *list)
{
	if (list->outfile > 0)
	    dup2(list->outfile, 1);
}

void	redir(t_list *list)
{
	pipe_set(list);
	redir_infile(list);
	redir_outfile(list);
	return ;
}
