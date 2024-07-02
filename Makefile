NAME = minishell

SRC_M = error.c \
        main.c \
        init_data.c \
        parsing.c\
		lexer.c\
		syntax_error.c\
		parsing1.c\

OBJ_M = $(SRC_M:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror  #-fsanitize=address -g3
LDFLAGS = -Llibft -lft -lreadline

all: $(NAME)

$(NAME): $(OBJ_M)
	@make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_M) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make clean -C libft
	rm -f $(OBJ_M)

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

