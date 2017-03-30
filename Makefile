EXE = ft_ls

HEADER = includes/ft_ls.h

SRCS = $(wildcard srcs/*.c$)

OBJS = $(subst srcs/,.objs/,$(SRCS:.c=.o))

LIBFT = libft/libft.a

LIB_DEPS = $(wildcard libft/*.c$)

CC = gcc

LINK = -L libft -lft

all : $(EXE)

$(EXE) : $(OBJS) $(HEADER)
	$(CC) .objs/*.o $(LINK) -o $(EXE)

.objs/%.o : srcs/%.c $(LIBFT)
	$(CC) -Iincludes -c -o $@ $<

$(LIBFT) : $(LIB_DEPS)
	make -C libft

.PHONY : clean fclean re

clean :
	rm -f .objs/*.o$

fclean : clean
	rm -f $(EXE)

re : fclean all
