/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:13:28 by kyjo              #+#    #+#             */
/*   Updated: 2023/08/19 10:14:06 by kyjo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

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
# include <fcntl.h>
# include <signal.h>    //나머지
# include <termios.h> //ㅌㅓ미널 속성

#endif