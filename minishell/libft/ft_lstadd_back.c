/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:52:20 by kyjo              #+#    #+#             */
/*   Updated: 2022/11/19 12:57:41 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp_list;

	if (new == NULL)
		return ;
	temp_list = NULL;
	if (*lst)
	{
		temp_list = ft_lstlast(*lst);
		temp_list->next = new;
	}
	else
		*lst = new;
}
