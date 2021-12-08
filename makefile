# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tigerber <tigerber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 15:56:05 by tnave             #+#    #+#              #
#    Updated: 2021/12/08 13:31:44 by tigerber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =  minishell.c								\
		parsing.c								\
		les_print.c								\
		ft_lst.c 								\
		parsing2.c 								\
		file_cmd.c 								\
		file_cmd_redir.c 						\
		built_in.c 								\
		pipex/exit_error.c						\
		pipex/ft_lst.c							\
		pipex/ft_split.c						\
		pipex/parsing.c 						\
		pipex/pipex.c							\
		pipex/utils_two.c						\
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
