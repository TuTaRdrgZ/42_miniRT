NAME = miniRT

SRCS = src/main.c src/struct_init.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -g -lglfw -L"/Users/renebarbierperez/homebrew/Cellar/glfw/3.4/lib/" #-Wall -Wextra -Werror

INC = inc/miniRT.h

MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit
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
