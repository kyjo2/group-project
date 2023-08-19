/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:13:28 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/19 10:58:53 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

int 	in_out(t_list *list);
int	    command_check(t_list *list);
int	    other_cmd(t_list *list, t_env *env);
void	redir(t_list *list);
void	heredoc(t_list *list);
void	cut_av(t_list *list, char *str, int size);
char	*get_cmd(char **path, char *list);

#endif