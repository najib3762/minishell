
NAME = minishell

SRC_M = parsing/error.c \
        parsing/init_data.c \
        parsing/utile_token2.c\
		parsing/lexer.c\
		parsing/syntax_error.c\
		parsing/parsing1.c\
		parsing/r_quotes.c\
		parsing/parsing2.c\
		parsing/utils3.c\
		parsing/utils4.c\
		here_doc/here_doc.c\
		here_doc/here_doc1.c\
		here_doc/here_doc_utils.c\
		here_doc/here_doc_expand.c\
		expand/expand.c\
		expand/expand_utils.c\
		expand/expand_utils2.c\
		redirections/redirections1.c\
		redirections/redirections2.c\
		redirections/pipes.c\
		main.c \
		free.c\
		execution/execution.c\
		Built_in/Built-in2.c\
		Built_in/Built-in.c\
		Built_in/Built-in_utils.c\
		signal.c\

		

OBJ_M = $(SRC_M:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -g3
LDFLAGS = -Llibft -lft -lreadline

all: $(NAME)

$(NAME): $(OBJ_M)
	@make -C libft
	@make bonus -C libft
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
