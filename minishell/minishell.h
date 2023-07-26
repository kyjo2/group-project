/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:44:36 by junggkim          #+#    #+#             */
/*   Updated: 2023/07/26 12:40:18 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <dirent.h>  //opendir,closedir,readdir
# include <term.h>  //
# include <stdio.h>  //tgetstr,tgoto,tgetent,tgetflag,tgetnum,tputs
# include <sys/termios.h> //tcsetattr, tcgetattr
# include <sys/ioctl.h>
# include <sys/wait.h> // ioctl,wait3,wait4
# include <unistd.h> // STDIN_FILENO표준입력
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>    //나머지
# include <termios.h> //ㅌㅓ미널 속성

typedef struct s_list
{
	int				ac;
	char			**av;
	char			*cmd;
    char            **envp;
	int				exist_pipe;
	int				pipe[2];
	int				infile;
	int				outfile;
	int             re_flag;
	struct s_list   *next;
}   t_list;
 
typedef	struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

#endif
