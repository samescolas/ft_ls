# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sescolas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/06 12:39:43 by sescolas          #+#    #+#              #
#    Updated: 2017/03/06 19:57:52 by sescolas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS = \
	   srcs/main.c \
	   srcs/options.c

OBJS = $(subst srcs/,,$(SRCS:.c=.o))

LINKS = -L libft -lft

INCLUDE = -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	gcc -o $(NAME) $(OBJS) $(LINKS) $(INCLUDE)

$(OBJS): $(SRCS)
	gcc -c $(SRCS) $(INCLUDE)

clean:
	make clean -C libft
	rm -f *\.o

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
