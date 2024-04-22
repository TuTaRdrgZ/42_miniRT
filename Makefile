NAME = miniRT

SRCS = src/main.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -g#-Wall -Wextra -Werror

INC = inc/miniRT.h

MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm
MLXLIB = lib/MLX42/build/libmlx42.a
VECTOR = lib/vector/vector.a
CC = gcc

%c.o: %.c 
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(INC)
	$(CC) $(CFLAGS) $(OBJS) $(VECTOR) $(MLXLIB) $(MLXFLAGS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	make all

re: fclean all

.PHONY: all clean fclean re
