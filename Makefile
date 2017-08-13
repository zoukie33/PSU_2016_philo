##
## Makefile for philo in /home/gadrat_r/delivery/PSU_2016_philo
## 
## Made by Romain Gadrat
## Login   <gadrat_r@epitech.net>
## 
## Started on  Mon Mar 13 19:38:55 2017 Romain Gadrat
## Last update Thu Mar 16 04:09:55 2017 zoukie
##

CC	=	gcc

NAME	=	philo

SRC	=	pastisolophe.c	\
		solosophe.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-I./include/ -W -Wall -Wextra -pedantic

LDFLAGS =	-L. -lriceferee -Wl,-rpath=. -lpthread

RM	=	rm -fr

all	:	$(NAME)

$(NAME)	:	$(OBJ)

		$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean	:

		$(RM) $(OBJ)

fclean	:	clean

		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re

