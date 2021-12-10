# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 15:56:05 by tnave             #+#    #+#              #
#    Updated: 2021/12/10 17:58:10 by tigerber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =  srcs/minishell.c								\
		srcs/prompt.c									\
		srcs/utils.c 									\
		srcs/error.c 									\
		srcs/parsing/environement.c						\
		srcs/parsing/parsing.c							\
		srcs/parsing/parsing_dollars.c					\
		srcs/parsing/parsing2.c 						\
		srcs/parsing/file_cmd.c 						\
		srcs/parsing/file_cmd_redir.c 					\
		srcs/utils_lst/ft_lst_env.c 					\
		srcs/utils_lst/ft_lst_action.c 					\
		srcs/utils_lst/ft_lst_shell.c 					\
		srcs/utils_lst/ft_lst_dollars.c 				\
		srcs/built_in/built_in.c 						\
		srcs/built_in/built_in_cd_pwd.c 				\
		srcs/built_in/built_in_export.c 				\
		srcs/built_in/built_in_export_utils.c			\
		srcs/built_in/built_in_unset.c 					\
		srcs/built_in/built_in_echo.c 					\
		srcs/built_in/built_in_exit.c 					\
		les_print.c										\
		pipex/exit_error.c								\
		pipex/ft_lst.c									\
		pipex/ft_split.c								\
		pipex/parsing.c 								\
		pipex/pipex.c									\
		pipex/utils_two.c								\
		pipex/utils.c

CC = clang

CFLAGS = -Wall -Wextra -g3 -I ./include/

HEADER = -I ./includes/

OBJ = $(SRCS:%.c=%.o)

LIBS = -lreadline

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

all: $(NAME)

%.o%.c:
	$(CC) -c $(CFLAGS) -I $(HEADER) $< -o ${<:.c=.o}

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
