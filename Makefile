CCC = cc -Wall -Wextra -Werror
Name = exec
Libft = Libft/libft.a
files = Built-in.c 

all : $(NAME)

$(LIBFT):
	@echo "Making $(notdir $@)... ⏳"
	@make -C Libft all > /dev/null
	@echo "Done ✅"

$(NAME) : $(files) $(LIBFT) 
	@echo "Making $@... ⏳"
	@$(CCF) $(files) -o $(NAME) $(LIBFT)  > /dev/null
	@echo "Done ✅"

.PHONY: clean fclean re bonus

clean:
	@$(MAKE) -C Libft clean > /dev/null
	@echo "Cleaning executables...✅"

fclean: clean
	@$(MAKE) -C Libft fclean > /dev/null
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "Full clean done...✅"

re: fclean all