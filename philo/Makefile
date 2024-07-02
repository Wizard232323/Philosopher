# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekoubbi <ekoubbi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 16:16:19 by ekoubbi           #+#    #+#              #
#    Updated: 2024/07/01 18:16:49 by ekoubbi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo

CC 		= cc
RM 		= rm -f

CFLAGS 	= -Wall -Wextra -Werror -g #-fsanitize=thread #-fsanitize=address 
CLINKS	= -lpthread

SRC 	= utils.c\
		  philo.c\
		  init.c\
		  action.c\
		  death_control.c

OBJ_PHILO := $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ_PHILO)
	$(CC) $(CFLAGS) $(OBJ_PHILO) -o $(NAME) $(CLINKS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ_PHILO)

fclean : clean
	rm -f $(NAME)

re : fclean all



