# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 15:56:05 by tnave             #+#    #+#              #
#    Updated: 2022/01/18 14:13:12 by tigerber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =  srcs/minishell.c								\
		srcs/execve/execve.c							\
		srcs/execve/utils_execve_two.c					\
		srcs/execve/parse_env_two.c						\
		srcs/execve/opt_exec_mini.c						\
		srcs/execve/opt_exec_mini_two.c					\
		srcs/redirec/redirection.c						\
		srcs/redirec/herdoc.c							\
		srcs/redirec/utils_convert_dol_herdoc.c 		\
		srcs/prompt/prompt.c							\
		srcs/prompt/prompt_two.c						\
		srcs/utils_and_clear/utils_buff.c 				\
		srcs/utils_and_clear/utils_buff_two.c 			\
		srcs/utils_and_clear/utils_two.c				\
		srcs/utils_and_clear/outils.c 					\
		srcs/utils_and_clear/error.c 					\
		srcs/utils_and_clear/clear.c 					\
		srcs/parsing/environement.c						\
		srcs/parsing/stock_env_home.c					\
		srcs/parsing/parsing_for_token.c				\
		srcs/parsing/parsing_for_token_two.c			\
		srcs/parsing/parsing_dollars.c					\
		srcs/parsing/parsing_dollars_two.c				\
		srcs/parsing/utils_parsing_dollars.c			\
		srcs/parsing/parsing_error_token.c 				\
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
		srcs/utils_and_clear/ft_split.c					\
		srcs/utils_and_clear/clear_two.c				\
		srcs/utils_and_clear/clear_three.c			

CC = clang

CFLAGS = -Wall -Wextra -Werror -I ./include/ -g3

HEADER = -I ./includes/

OBJ = $(SRCS:%.c=%.o)

LIBS = -lreadline

ADDED = echo "\033[92m⚙️ ⚙️ ⚙️ ⚙️ ⚙️ SUCCESS\033[0m"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS) && $(ADDED)

MAKEFLAGS += --silent

all: $(NAME)

%.o%.c:
	$(CC) -c $(CFLAGS) -I $(HEADER) $< -o ${<:.c=.o}

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
