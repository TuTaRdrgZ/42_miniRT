NAME	:=	vector.a

###			###			COMPILER		###			###
CC		:=	"cc"
CFLAGS	:=	-Wall -Wextra -Werror

###			###			SOURCES			###			###
SRC		:=	ft_add_vectors.c
SRC		+=	ft_abs_vector.c
SRC		+=	ft_are_equal_vectors.c
SRC		+=	ft_subtract_vectors.c
SRC		+=	ft_multiply_vectors.c
SRC		+=	ft_multiply_vector_by_scalar.c
SRC		+=	ft_divide_vector_by_scalar.c
SRC		+=	ft_dot_product.c
SRC		+=	ft_cross_product.c
SRC		+=	ft_normalize_vector.c
SRC		+=	ft_new_vector.c
SRC		+=	ft_invert_vector.c
SRC		+=	ft_length_vector.c
SRC		+=	ft_length_squared.c
SRC		+=	ft_print_vector.c

###			###			OBJECTS			###			###
OBJ_D	:=	./obj
SRCOBJ	:=	$(patsubst %.c,$(OBJ_D)/%.o,$(SRC))

###			###			COLORS			###			###
RED = \033[1;31m
GREEN = \033[1;32m
YELL = \033[1;33m
BLUE = \033[1;34m
WHITE = \033[0m

###			###			RULES			###			###
all: $(OBJ_D) $(NAME)

$(NAME): $(SRCOBJ)
	@ar -rcs $(NAME) $^
	@printf "$(RED)--->$(BLUE)Libvec is compiled.$(WHITE)"

$(OBJ_D)/%.o: %.c message
	@$(CC) $(CFLAGS) -c $< -o $@

message:
	@echo "$(BLUE)--->$(GREEN)Compiling C Files .....$(WHITE)"

$(OBJ_D):
	@mkdir $@

clean:
	@/bin/rm -rf $(OBJ_D) libvec.h.gch

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		/bin/rm -f $(NAME); \
	fi;

re: fclean all

.PHONY: all clean fclean re

.INTERMEDIATE: message
