NAME = miniRT

SRCS = src/main.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -g#-Wall -Wextra -Werror

INC = inc/miniRT.h

MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm
MLXLIB = lib/MLX42/build/libmlx42.a
VECTOR = lib/vector/vector.a
LIB = lib/
CC = gcc

%c.o: %.c 
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(INC)
	@make -C lib/vector
	@make -C lib/libft/
	$(CC) $(CFLAGS) $(OBJS) $(VECTOR) $(MLXLIB) $(MLXFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)
	@make clean -C lib/libft
	@make clean -C lib/vector

fclean: clean
	rm -f $(NAME)
	@make fclean -C lib/libft
	@make fclean -C lib/vector

re: fclean all

.PHONY: all clean fclean re
