# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyjo <kyjo@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 12:10:36 by kyjo              #+#    #+#              #
#    Updated: 2023/09/09 13:59:32 by kyjo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

LIB = libminishell.a

READ = -lreadline

AR = ar

AFLAGS = rcs

LIBFT = -lft -L./libft

MINI = -lminishell -L.

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
	path.c \
	./execute/execute.c \
	./execute/heredoc.c \
	./execute/command.c \
	./execute/inout.c \
	./execute/redir.c \
	./execute/syntax.c \
	./execute/free.c \
	./builtin/ft_cd.c \
	./builtin/ft_cd2.c \
	./builtin/ft_echo.c \
	./builtin/ft_env.c \
	./builtin/ft_exit.c \
	./builtin/ft_export.c \
	./builtin/ft_export2.c \
	./builtin/ft_pwd.c \
	./builtin/ft_unset.c \
	./parsing/parsing.c \
	./parsing/parsing2.c\
	./parsing/utils.c\
	./parsing/new_split.c\
	./parsing/new_split2.c\
	./libft/ft_strcmp.c\
	./libft/ft_itoa.c \


OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I${HOME}/.brew/opt/readline/include -c $^ -o $@ -I./ 

$(LIB) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(NAME) : $(LIB)
	make -C ./libft all
	$(CC) $(CFLAGS) $(LIBFT) $(MINI) $(READ) -L${HOME}/.brew/opt/readline/lib -o $@

clean :
	make -C ./libft clean
	rm -rf $(OBJS)

fclean : clean
	make -C ./libft fclean
	rm -rf $(LIB) $(NAME)

re : 
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re 
