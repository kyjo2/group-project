/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junggkim <junggkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:44:36 by junggkim          #+#    #+#             */
/*   Updated: 2023/09/07 20:53:30 by junggkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ 0
# define WRITE 1

# include "./libft/libft.h"
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

int	g_exit_code;

typedef struct s_list
{
	int				ac;
	char			**av;
	char			*cmd;
    char			**envp;
	int				exist_pipe;
	int				pip[2];
	int				infile;
	int				outfile;
	struct s_list   *next;
	struct s_list   *prev;  
}   t_list;
 
typedef	struct	s_env
{
	char			*name;
	char			*value;
	//char			*question_mark; //$? 일때 숫자
	int				have_equl;
	struct s_env	*next;
}				t_env;

typedef struct	s_info
{
	int				pipe_flag;
	int				quote_flag;
	int				doubleq_flag;
	int				singleq_flag;
	int				start;
	int				last_pid;
	int				count_doubleq;
	int				count_singleq;
	char			*question_mark; //$? 일때 숫자
	char			**envp;
	struct s_env	*envp_head;
}	t_info;

int 	in_out(t_list *list);
int	    command_check(t_list *list, t_info *info);
int	    other_cmd(t_list *list, t_info *info);
void	redir(t_list *list);
void	heredoc(t_list *list, int index);
void	cut_av(t_list *list, char *str, int size);
t_env	*find_env(char **ev);
char	**find_path(t_info *info);
int		execute(t_list *list, t_info *info);
void	parsing(t_list **list, char **line, t_info *info);
int		ft_cd(char **cmd, t_info *info);
int	    ft_echo(char **cmd);
//int	    ft_env(char	**env);
int		ft_env(t_env *env);
int		ft_exit(char **cmd, int flag);
int		ft_export(char **cmd, t_info *info);
int		ft_pwd(int fd, t_info *info);
int		ft_unset(char **cmd, t_info *info);
//parsing
void	ft_change_env(char **line, t_info *info, int i);
void	delete_quote(t_list *new, t_info *info);
void	change_env_space(char **line, int start);
void	ft_copy(char **line, char *value, int name_len, int start);
void    ft_error(char *str);
int	new_strcmp(const char *s1, const char *s2);
//static int	check_sep(char s, char c, t_info *info, int flag);
//static size_t	count_room(char const *s, char c, t_info *info);
//static void	*ft_free(char **result);
//static char	**sub_split(char **result, char const *s, char c, t_info *info);
char	**new_split(char const *s, char c, t_info *info);
void	change_env_export(t_info *info, char *name, char *value, int have_equl);
int		check_cmd(char *cmd);
char	*ft_itoa(int n);
//int		check_s1(char s1);
//static int	ft_len(const char *s);

#endif
