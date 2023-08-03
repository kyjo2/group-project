/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:32:03 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/03 12:37:43 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirect_pipe(t_list *list)
{
	if (list->exist_pipe)
    {
    	dup2(list->pipe[1], 1);
        dup2(list->next->pipe[0], 0);
    }
}

void	redirect_infile(t_list *list)
{
	if (list->infile > 0)
	    dup2(list->infile, 0);
}

void	redirect_outfile(t_list *list)
{
	if (list->outfile > 0)
	    dup2(list->outfile, 1);
}

void	redirect(t_list *list)
{
	redirect_pipe(list);
	redirect_infile(list);
	redirect_outfile(list);
	return ;
}
