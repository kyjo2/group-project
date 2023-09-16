/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:09:00 by kyjo              #+#    #+#             */
/*   Updated: 2023/09/16 23:27:28 by yul              ###   ########.fr       */
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
		{
			ret = WTERMSIG(status);
			if (ret == 2 || ret == 3)
				ret += 128;
		}
		else
			ret = WEXITSTATUS(status);
		if (temp == info->last_pid)
			g_exit_code = ret;
		temp = wait(&status);
	}
}

void	free_in_list(t_list *head)
{
	t_list	*temp;

	temp = head;
	while (temp)
	{
		if (temp->pip[READ] > 0)
			close(temp->pip[READ]);
		if (temp->pip[WRITE] > 0)
			close(temp->pip[WRITE]);
		if (temp->infile > 0)
			close(temp->infile);
		if (temp->outfile > 0)
			close(temp->outfile);
		temp = temp->next;
	}
}

void	unlink_tmp_file(void)
{
	int		i;
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
	while (i >= 0)
	{
		temp_number = ft_itoa(i);
		temp = ft_strjoin("temp_", temp_number);
		free(temp_number);
		unlink(temp);
		free(temp);
		i--;
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

void	delete_check_quote(char **line)
{
	int		i;
	int		k;

	k = -1;
	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == 12 && ((*line)[i + 1] == '\''
				|| (*line)[i + 1] == '\"'))
		{
			i++;
			(*line)[++k] = (*line)[i];
		}
		else
			(*line)[++k] = (*line)[i];
	}
	(*line)[++k] = '\0';
}
