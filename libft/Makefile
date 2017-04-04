# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sescolas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/13 09:59:58 by sescolas          #+#    #+#              #
#    Updated: 2017/02/28 18:32:25 by sescolas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = libft.h

SRCS = 	$(wildcard *.c)

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	ar rc $@ *\.o$
	ranlib $@

$(OBJS): $(SRCS) $(HEADER)

.PHONY: clean fclean re

clean:
	rm -f *\.o$

fclean: clean
	rm -f $(NAME)

re: fclean all
