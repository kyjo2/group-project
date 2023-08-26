/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yul <yul@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:44:36 by junggkim          #+#    #+#             */
/*   Updated: 2023/08/26 16:19:42 by yul              ###   ########.fr       */
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
	struct s_env	*next;
}				t_env;

typedef struct	s_info
{
	int				pipe_flag;
	int				quote_flag;
	int				doubleq_flag;
	int				singleq_flag;
	int				start;
	char			*question_mark; //$? 일때 숫자
	char			**envp;
	struct s_env	*envp_head;
}	t_info;

int 	in_out(t_list *list);
int	    command_check(t_list *list);
int	    other_cmd(t_list *list);
void	redir(t_list *list);
void	heredoc(t_list *list, int index);
void	cut_av(t_list *list, char *str, int size);
t_env	*find_env(char **ev);
int		execute(t_list *list);
void	parsing(t_list **list, char **line, t_info *info);
int		ft_cd(void);
int	    ft_echo(char *str);
int	    ft_env(char **envp);
int		ft_exit(void);
int		ft_export(void);
int		ft_pwd(int fd);
int		ft_unset(void);
//parsing
void	ft_change_env(char **line, t_info *info, int i, int doubleq_flag);
void	delete_quote(t_list *new, t_info *info);
void	change_env_space(char **line, t_info *info, int start);
void	ft_copy(char **line, char *value, int name_len, int start);
void    ft_error(char *str);
//static int	check_sep(char s, char c, t_info *info, int flag);
//static size_t	count_room(char const *s, char c, t_info *info);
//static void	*ft_free(char **result);
//static char	**sub_split(char **result, char const *s, char c, t_info *info);
char	**new_split(char const *s, char c, t_info *info);
//static int	ft_len(const char *s);

#endif


// void parcing(t_list *list, char *line, char **envp)
// {
// 	int i;
// 	int start;
// 	int pipe_flag;
// 	t_list *tmp;
// 	t_list *new;
// 	t_env	*change_env;
// 	int quote_flag;

// 	quote_flag = 0;
// 	i = 0;
// 	start = 0;
// 	pipe_flag = 1;
// 	while (1) // readline으로 입력받은 line을 모두 하나하나 체크하는 loop입니다.
// 	{
// 		if ((line[i] == '\"' || line[i] == '\'') && quote_flag == 0) // 파이프가 따옴표 안에 들어가는 경우 끊으면 안됨.
// 			quote_flag = 1;
// 		else if ((line[i] == '\"' || line[i] == '\'') && quote_flag == 1)
// 			quote_flag = 0;
// 		if (line[i] == '\0' || (line[i] == '|' && quote_flag == 0)) // 파이프를 기준으로 명령어를 나누기 위해 설정한 조건문입니다. null을 만날 경우, 이전까지의 명령어를 list의 노드로 생성합니다.
// 		{
// 			if (line[i] == '|')
// 			{
// 				line[i] = '\0'; // 파이프문자를 null로 바꾸어 split을 용이하게 합니다.
// 				list->exist_pipe = 1;
// 			}
// 			else
// 				pipe_flag = 0;
// 			if ((new = make_node(&line[start], pipe_flag, envp, change_env)) == 0) //make node
// 				return;
// 			if (start == 0)
// 			{
// 				list = new;
// 				tmp = list; //head_list
// 			}
// 			else // 처음 노드가 아니기 때문에 list가 존재하므로 next로 연결해줍니다.
// 			{
// 				(list)->next = new;
// 				list = (list)->next;
// 			}
// 			if (pipe_flag == 0) // 마지막 노드이므로 while loop를 벗어납니다.
// 				break;
// 			start = i + 1; // split할 명령어의 첫번째 index를 파이프의 다음 index로 갱신시켜줍니다.
// 		}
// 		i++;
// 	}
// 	list = tmp; // backup 해놨던 첫번째 명령어의 주소를 cmd_list에 넣어 반환합니다.
// }