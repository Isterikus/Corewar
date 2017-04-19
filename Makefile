# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/15 19:26:06 by dkovalen          #+#    #+#              #
#    Updated: 2017/03/30 16:22:52 by dkovalen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

NAME_COR = corewar

FLAGS = -Wall -Wextra -Werror -lncurses

LIBA = ./libft/libftprintf.a ./VM/libop.a

SRC_ERR = Asm/op.c Asm/asm.c Asm/make_new.c Asm/file1.c Asm/file2.c Asm/file3.c\
			Asm/file4.c Asm/file5.c Asm/file6.c Asm/file7.c

SRC_COR = VM/corewar.c VM/ft_live.c VM/op.c VM/file1.c VM/file2.c VM/file3.c\
			VM/file4.c VM/file5.c VM/file6.c VM/file7.c

SRC_ERR_O = $(SRC_ERR:.c=.o)

SRC_COR_O = $(SRC_COR:.c=.o)

all: $(NAME)

$(NAME): $(SRC_ERR_O) $(SRC_COR_O)
	@ make -C ./libft
	@ make re -C ./VM
	gcc $(FLAGS) $(SRC_ERR_O) $(LIBA) -o $(NAME)
	gcc $(FLAGS) $(SRC_COR_O) $(LIBA) -o $(NAME_COR)

debug :
	@ make -C ./libft
	gcc -lncurses -o $(NAME_COR) -g ./VM/*.c ./libft/libftprintf.a

drun : debug
	lldb $(NAME_COR)

%.o: %.c
	gcc -c -Wall -Wextra -Werror -o $@ $<

clean:
	@ make clean -C ./libft
	@ make clean -C ./VM
	rm -f $(SRC_ERR_O) $(SRC_COR_O)

fclean: clean
	rm -f $(NAME) $(NAME_COR) $(LIBA)

re: fclean all
