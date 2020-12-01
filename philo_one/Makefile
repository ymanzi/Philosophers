# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymanzi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 14:05:13 by ymanzi            #+#    #+#              #
#    Updated: 2020/11/22 13:49:15 by ymanzi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = philo.a
CFLAGS = -Wall -Wextra -Werror 
SRCS = main.c init.c check.c main_loop.c utils.c write_fct.c

OBJ = $(SRCS:.c=.o)
EXEC = philo_one

all:
	gcc $(CFLAGS) $(SRCS) -o $(EXEC)

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
clean:
		rm -f $(EXEC)
fclean: clean
re: fclean all
