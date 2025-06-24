CC  = cc
CFLAGS = -Wall -Wextra -Werror -g3 -I libft
NAME = pipex
DEPS = pipex.h
SRCS = pipex.c src/get_path.c src/set_to_path.c
OBJS = $(SRCS:.c=.o)
LIBDIR = ./libft
LIBMAKE = $(LIBDIR)/libft.a

all: $(NAME) 

$(NAME) : $(OBJS) $(LIBMAKE)
	$(CC) $(CFLAGS) $(OBJS) $(LIBMAKE) -o $(NAME)

$(LIBMAKE):
	make -C $(LIBDIR)

%.o : %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBDIR)
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -f  $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
