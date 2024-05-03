NAME = miniRT

RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[93m
CYAN = \033[96m

SRCS = src/parser/ambient.c \
	   src/parser/camera.c \
	   src/parser/checkfile.c \
	   src/parser/checktype.c \
	   src/parser/checkobj.c \
	   src/parser/light.c \
	   src/parser/coordinates.c \
	   src/parser/readfile.c \
	   src/parser/utils.c \
	   src/parser/utils2.c \
	   src/parser/RGB.c
SRCS += src/struct_init.c \
		src/main.c
SRCS += src/objects/init_objects.c \
		src/objects/init_light.c \
		src/objects/list_utils.c
SRCS += src/intersection/hit_sphere.c \
		src/intersection/hit_any.c

OBJS = $(SRCS:.c=.o)

CFLAGS = -Iinc/ -g -Wall -Wextra -Werror -Wno-misleading-indentation -Wno-implicit-fallthrough

INC = inc/miniRT.h \
	  inc/structures.h
	  # inc/parser.h

SILENCE = --no-print-directory

MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm -Ilib/
MLXLIB = lib/MLX42/build/libmlx42.a
VECTOR = lib/vector/vector.a
LIBFTLIB = lib/libft/libft.a
LIB = lib/
CC = gcc

%c.o: %.c $(INC)
	@printf "\033[0;33mGenerating miniRT objects... %-33.33s\r"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(INC) Makefile
	@make -C lib/vector $(SILENCE)
	@make -C lib/libft/ $(SILENCE)
	$(CC) $(CFLAGS) $(OBJS) $(VECTOR) $(LIBFTLIB) $(MLXLIB) $(MLXFLAGS) -o $(NAME)
	@echo ""
	@echo "$(YELLOW)miniRT $(RESET)$(CYAN)$(BOLD)created$(RESET)"

clean:
	@rm -f $(OBJS)
	@make clean -C lib/libft $(SILENCE)
	@make clean -C lib/vector $(SILENCE)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C lib/libft $(SILENCE)
	@make fclean -C lib/vector $(SILENCE)

re: fclean all

.PHONY: all clean fclean re
