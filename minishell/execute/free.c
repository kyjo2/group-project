/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:09:00 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/10 09:36:52 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (ret == 2 || ret == 3)
			ret += 128;
		if (ret == 255)
			ret -= 128;
		if (temp == info->last_pid)
			g_exit_code = ret;
		temp = wait(&status);
	}
}

void	free_in_list(t_list *head)
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
		head = head->next;
	}
}

void	unlink_tmp_file(void)
{
	int		i;
	int		j;
	char	*temp;
	char	*temp_number;

	i = 0;
	while (1)
	{
		temp_number = ft_itoa(i);
		temp = ft_strjoin("temp_", temp_number);
		free(temp_number);
		if (open(temp, O_RDONLY) < 0)
			break ;
		i++;
		free(temp);
	}
	free(temp);
	j = 0;
	while (j < i)
	{
		temp = ft_strjoin("temp_", ft_itoa(j));
		unlink(temp);
		free(temp);
		j++;
	}
}

void	deep_free(char **temp)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	temp = NULL;
}
