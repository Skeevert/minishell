OBJS = srcs/main.o \
			 srcs/user_input.o

FLAGS = -Wall -Wextra -Werror

LIB_NAME = srcs/libft/libft.a
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	make -C srcs/libft
	gcc $(FLAGS) $(OBJS) $(LIB_NAME) -o $@

$(OBJS): %.o: %.c
	gcc -c $(FLAGS) $< -o $@ -I./includes -I./srcs/libft

clean:
	make -C srcs/libft clean
	rm -f $(OBJS)

fclean: clean
	make -C srcs/libft fclean
	rm -f $(NAME)

re: fclean all
