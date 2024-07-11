# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artmarti <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 08:06:32 by artmarti          #+#    #+#              #
#    Updated: 2023/07/24 11:33:30 by artmarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ALLFILES = philosophers.c monitor.c dinner.c utils.c

OBJECTS = $(ALLFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = philo

all : $(NAME)
	
$(NAME) :
	gcc $(CFLAGS) $(ALLFILES) -pthread -o philo

clean :
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
