CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRCS = ft_printf.c p_add.c p_char.c p_hex.c p_num.c p_str.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	cc -c $(CFLAGS) -o $@ $<
	ar rcs $(NAME) $@
$(NAME) : $(OBJS)


.PHONY : clean fclean re

fclean : clean
	rm -f $(NAME)

clean :
	rm -f $(OBJS)

re : fclean clean all