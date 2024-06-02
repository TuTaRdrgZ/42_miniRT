NAME = miniRT

########## COLORS ##########
RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[93m
CYAN = \033[96m

########## DIRECTORIES ##########

DIR_SRC = src/
DIR_INT = intersection/
DIR_PAR = parser/
DIR_OBJ = objects/
DIR_UTI = utils/
DIR_RAY = rays/
DIR_VEC = vectors/
DIR_BUILD = .build/

########## FILES ##########

FILE_MAIN = main.c
FILES_OBJ = init_objects.c init_light.c 
FILES_PAR = ambient.c camera.c checkfile.c checktype.c checkobj.c light.c \
			coordinates.c readfile.c utils.c utils2.c check_dup.c RGB.c
FILES_INT = hit_sphere.c hit_plane.c hit_cylinder.c hit_any.c
FILES_UTI = get_color.c struct_init.c
FILES_RAY = compute_rays.c lighting.c
FILES_VEC = add_vectors.c cross_product.c distance_vector.c divide_vector_by_scalar.c \
			dot_product.c length_vector.c multiply_vector_by_scalar.c new_vector.c \
			normalize_vector.c subtract_vectors.c

########## SOURCES ##########

SRC_MAIN = $(addprefix $(DIR_SRC), $(FILE_MAIN))
SRC_OBJ = $(addprefix $(DIR_SRC), $(addprefix $(DIR_OBJ), $(FILES_OBJ)))
SRC_PAR = $(addprefix $(DIR_SRC), $(addprefix $(DIR_PAR), $(FILES_PAR)))
SRC_INT = $(addprefix $(DIR_SRC), $(addprefix $(DIR_INT), $(FILES_INT)))
SRC_UTI = $(addprefix $(DIR_SRC), $(addprefix $(DIR_UTI), $(FILES_UTI)))
SRC_RAY = $(addprefix $(DIR_SRC), $(addprefix $(DIR_RAY), $(FILES_RAY)))
SRC_VEC = $(addprefix $(DIR_SRC), $(addprefix $(DIR_VEC), $(FILES_VEC)))

########## OBJECTS ##########

OBJ_MAIN = $(addprefix $(DIR_BUILD), $(FILE_MAIN:.c=.o))
OBJ_OBJ = $(addprefix $(DIR_BUILD), $(addprefix $(DIR_OBJ), $(FILES_OBJ:.c=.o)))
OBJ_PAR = $(addprefix $(DIR_BUILD), $(addprefix $(DIR_PAR), $(FILES_PAR:.c=.o)))
OBJ_INT = $(addprefix $(DIR_BUILD), $(addprefix $(DIR_INT), $(FILES_INT:.c=.o)))
OBJ_UTI = $(addprefix $(DIR_BUILD), $(addprefix $(DIR_UTI), $(FILES_UTI:.c=.o)))
OBJ_RAY = $(addprefix $(DIR_BUILD), $(addprefix $(DIR_RAY), $(FILES_RAY:.c=.o)))
OBJ_VEC = $(addprefix $(DIR_BUILD), $(addprefix $(DIR_VEC), $(FILES_VEC:.c=.o)))

OBJ_ALL = $(OBJ_MAIN) $(OBJ_OBJ) $(OBJ_PAR) $(OBJ_INT) $(OBJ_UTI) $(OBJ_RAY) $(OBJ_VEC)

DEP_FILES = $(OBJ_ALL:.o=.d)

########## FLAGS ##########

MLXFLAGS = -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib/"		#·reneHome·#
#MLXFLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"		#·rene42·#
#MLXFLAGS = -Iinclude -ldl -lglfw -pthread -lm -Ilib/MLX42				#·tuta·#

MLXLIB = lib/MLX42/build/libmlx42.a
LIBFTLIB = lib/libft/libft.a
CC = cc

14_3_FLAG = -mmacosx-version-min=14.3
WARNING_FLAGS = -Wall -Wextra -Werror -Wno-misleading-indentation -Wno-implicit-fallthrough
SANITIZE_FLAGS = -g3 -fsanitize=address
DEPENDENCY_FLAGS = -MMD -MP
INCLUDES = -I inc -I lib/libft -I lib/MLX42

FLAGS = $(INCLUDES) $(WARNING_FLAGS) $(SANITIZE_FLAGS) $(DEPENDENCY_FLAGS) $(14_3_FLAG)

INC = inc/miniRT.h inc/structures.h #inc/parser.h

SILENCE = --no-print-directory

########## RULES ##########

all: $(DIR_BUILD) $(NAME)

$(DIR_BUILD):
	@mkdir -p $(DIR_BUILD)$(DIR_OBJ)
	@mkdir -p $(DIR_BUILD)$(DIR_PAR)
	@mkdir -p $(DIR_BUILD)$(DIR_INT)
	@mkdir -p $(DIR_BUILD)$(DIR_UTI)
	@mkdir -p $(DIR_BUILD)$(DIR_RAY)
	@mkdir -p $(DIR_BUILD)$(DIR_VEC)

$(DIR_BUILD)%.o: $(DIR_SRC)%.c $(INC) Makefile
	@printf "\033[0;33mGenerating miniRT objects... %-33.33s \r\033[0m" $@
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(DIR_BUILD) $(OBJ_ALL) $(INC)
	@make -C lib/libft/ $(SILENCE)
	@cmake -S lib/MLX42 -B lib/MLX42/build
	@make -C lib/MLX42/build
	@$(CC) $(FLAGS) $(OBJ_ALL) $(LIBFTLIB) $(MLXLIB) $(MLXFLAGS) -o $(NAME)
	@echo "\n$(YELLOW)miniRT $(RESET)$(CYAN)$(BOLD)created$(RESET)"

clean:
	@rm -fr $(DIR_BUILD)
	@rm -f  lib/MLX42/build/CMakeCache.txt
	@make clean -C lib/libft $(SILENCE)
	make clean -C lib/MLX42/build

fclean: clean
	@rm -f $(NAME)
	@make fclean -C lib/libft $(SILENCE)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP_FILES)