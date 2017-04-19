# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/24 11:59:59 by adzikovs          #+#    #+#              #
#    Updated: 2017/03/25 15:48:55 by dkovalen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libop.a
CC = gcc
CFLAGS = 
SRCS = base_funcs.c\
		ft_op_1.c\
		ft_op_2.c\
		ft_op_3.c\
		ft_op_4.c\
		ft_op_arr.c\
		ft_clist_push_back.c\
		serv_funcs.c
OBJECTS = base_funcs.o\
		ft_op_1.o\
		ft_op_2.o\
		ft_op_3.o\
		ft_op_4.o\
		ft_op_arr.o\
		ft_clist_push_back.o\
		serv_funcs.o

all : $(NAME)

$(NAME) : $(OBJECTS) 
	ar rc $(NAME) $(OBJECTS)

debug :
	$(CC) -g $(CFLAGS) -o $(NAME) main.c $(SRCS) ft_printf/*.c -I
	lldb $(NAME)

drun : debug
	./$(NAME)

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
