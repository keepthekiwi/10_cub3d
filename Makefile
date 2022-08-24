

CC = gcc

# LDFLAGS= -L/Users/$(USER)/.brew/opt/readline/lib -lreadline

CFLAGS = -Wall -Wextra -g -Iincludes -Werror #-I/Users/$(USER)/.brew/opt/readline/include

LIBFT = libft/libft.a
MLX_LIB_DIR	=	MLX42

INCLUDES = cub3d.h
NAME = cub3d

SRC_DIR = src
SRC_FILES =		src/main.c \
				src/handle_input.c \
				src/error_management.c \
				src/check_map.c \
				src/raycaster.c \
				src/raycaster_two.c \
				src/create_map.c \
				src/check_metadata.c \
				src/set_metadata_color.c \
				src/set_metadata_texture.c \
				src/free.c \
				src/create_world.c \
				src/textures.c \
				src/movements.c


T_OBJ = $(SRC_FILES:c=o)

MLX_LIB		= $(MLX_LIB_DIR)/libmlx42.a -lglfw -L "$(HOME)/.brew/Cellar/glfw/3.3.8/lib"
LIB_DIR = inc/
LIB_FILES = cub3d.h

OBJ_DIR = output/
OBJ = $(addprefix $(OBJ_DIR), $(T_OBJ))

# ------------------------------ Colors --------------------------------

BOLD_PURPLE	=	\033[1;35m
BOLD_CYAN	=	\033[1;36m
BOLD_YELLOW	=	\033[1;33m
GREEN		=	\033[32m
NO_COLOR	=	\033[0m

# ------------------------------ Messages ------------------------------

START			=	echo "\n🚧 $(BOLD_YELLOW)Make:	$(NO_COLOR)Starting the compilation..."
LIBFT_READY		=	echo "✅ $(GREEN)READY:	$(NO_COLOR)libft"
READY			=	echo "✅ $(GREEN)READY:	$(NO_COLOR)cub3d\n"
CLEANED			=	echo "\n💧 $(BOLD_YELLOW)Clean: $(NO_COLOR)Removed all the \".o\" files"
FCLEANED		=	echo "🧼 $(BOLD_YELLOW)Fclean: $(NO_COLOR)Removed the executables\n"

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ) $(SA_PATH) $(LIB_PATH)
	@$(START)
	@$(LIBFT_READY)
	@$(CC) -o $@ $(OBJ) -Llibft -lft ./libft/libft.a $(LDFLAGS) $(MLX_LIB)
	@$(READY)

$(OBJ_DIR):
	mkdir $(OBJ_DIR) $(OBJ_DIR)src

$(OBJ_DIR)%.o: %.c $(LIB_DIR)$(LIB_FILES)
	$(CC) -c $< -o $@ 
# cflag weider hinzufuegen

$(LIBFT):
	make -C libft
	make -C mlx42

all: $(NAME)

bonus: all

clean:
	@rm -rf $(OBJ_DIR)
	@$(CLEANED)

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@make -C mlx42 fclean
	@$(FCLEANED)

readline: $(READLINE_PATH)

re: fclean all


# @mv *.o $(OBJ_DIR)