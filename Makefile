NAME = ft_ls

HEADER = includes/ft_ls.h

SRCS = $(wildcard srcs/*.c$)

OBJS = $(subst srcs/,.objs/,$(SRCS:.c=.o))

LIBFT = libft/libft.a

LIB_DEPS = $(wildcard libft/*.c$)

CC = gcc

LINK = -L libft -lft

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	$(CC) .objs/*.o $(LINK) -o $(NAME)

.objs/%.o : srcs/%.c $(LIBFT)
	$(CC) -I includes -c -o $@ $<

$(LIBFT) : $(LIB_DEPS)
	make -C libft

.PHONY : clean fclean re

clean :
	rm -f libft/*\.o$
	rm -f .objs/*\.o$

fclean : clean
	rm -f $(NAME)

re : fclean all
