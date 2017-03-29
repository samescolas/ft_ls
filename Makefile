# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sescolas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 12:39:43 by sescolas          #+#    #+#              #
#    Updated: 2017/03/24 19:31:09 by sescolas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Werror -Wextra

NAME = ft_ls

SRCS =							\
	   srcs/main.c				\
	   srcs/options.c			\
	   srcs/scandir.c			\
	   srcs/print.c				\
	   srcs/cmp.c				\
	   srcs/long.c				\
	   srcs/long2.c				\
	   srcs/formatting.c		\
	   srcs/tree.c				\
	   srcs/tree2.c				\
	   srcs/init.c				\


OBJS = $(subst srcs/,,$(SRCS:.c=.o))

LINKS = -Llibft -lft

INCLUDE = -Iincludes

LFT = -C libft

all: $(NAME)

$(NAME):
	make $(LFT)
	$(CC) $(FLAGS) -c $(SRCS) $(INCLUDE)
	$(CC) $(LINKS) $(OBJS) -o $(NAME)


clean:
	make clean $(LFT)
	rm -f *\.o

fclean: clean
	make fclean $(LFT)
	rm -f $(NAME)

re: fclean all
