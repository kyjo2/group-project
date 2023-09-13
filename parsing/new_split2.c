/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:34:00 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/08 20:34:39 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_variable2(size_t *i, size_t *j, size_t *room)
{
	(*i) += (*j);
	(*room)++;
}

void	change_variable1(size_t *i, size_t *room)
{
	(*i) = 0;
	(*room) = 0;
}
