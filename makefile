# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnave <tnave@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/03 15:56:05 by tnave             #+#    #+#              #
#    Updated: 2021/08/03 15:56:11 by tnave            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =  get_next_line/get_next_line_utils.c 	\
		get_next_line/get_next_line.c 			\
		minishell.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I ./include/

HEADER = -I ./includes/

OBJ = $(SRCS:%.c=%.o)

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
