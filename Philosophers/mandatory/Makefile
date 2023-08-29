# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msekhsou <msekhsou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 11:17:53 by msekhsou          #+#    #+#              #
#    Updated: 2023/05/09 11:17:56 by msekhsou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c parsing.c philo_utils.c philo_infos.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

