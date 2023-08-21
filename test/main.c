/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 21:31:52 by yul               #+#    #+#             */
/*   Updated: 2023/08/21 23:22:32 by yul              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **av, char **ev)
{
	t_list			*list;
	char			*line;

	line = NULL;
	list = malloc(sizeof(t_list));
	list->av = av;
	list->ac = argc;
	while (1)
	{
		line = readline("minishell $ ");
		list->av = ft_split(line, ' ');
		list->ac = 5;
		list->cmd = NULL;
		list->envp = ev;
		list->exist_pipe = 0;
		list->infile = -2;
		list->outfile = -2;
		list->str = NULL;
		list->next = NULL;
		list->prev = NULL;
		if (!line) // EOF 처리 : ctr + d
			break;
		if (*line != '\0')
			add_history(line);
		/* 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 */
		if (*line != '\0') // 프롬프트상에서 입력된 문자가 null || 모두 white_space일 
		{
			execute(list);
		}
		free(line);
	}
}