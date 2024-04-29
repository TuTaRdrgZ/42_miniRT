NAME = miniRT

SRCS = src/parser/ambient.c \
	   src/parser/camera.c \
	   src/parser/checkfile.c \
	   src/parser/light.c \
	   src/parser/coordinates.c \
	   src/parser/readfile.c \
	   src/parser/utils.c \
	   src/parser/utils2.c \
	   src/parser/RGB.c
SRCS += src/struct_init.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Iinc/ -g -Wall -Wextra -Werror

INC = inc/miniRT.h \
	  inc/parser.h

MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm -Ilib/
MLXLIB = lib/MLX42/build/libmlx42.a
VECTOR = lib/vector/vector.a
LIBFTLIB = lib/libft/libft.a
LIB = lib/
CC = gcc

%c.o: %.c 
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(INC)
	@make -C lib/vector
	@make -C lib/libft/
	$(CC) $(CFLAGS) $(OBJS) $(VECTOR) $(LIBFTLIB) $(MLXLIB) $(MLXFLAGS) -o $(NAME)

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
