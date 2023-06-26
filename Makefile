# #================================== OS detecter ==============================
OS			= $(shell uname -s)
# #=============================================================================

LIB			= libs/
# #=============== wish flags to use to compile depending on the os ============
ifeq ($(OS), Darwin)
	MLXCC	= -L $(LIB)minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit 
	MLX_PATH	= mlx
else
	MLXCC = -L $(LIB)minilibx-linux -lmlx -lm -lX11 -lXext -lpthread
	MLX_PATH	= mlx_linux
endif
# #======================================================================================

# #====================================== Colors ========================================
NO_COLOR	= \033[0m
GRAY		= \033[0;1;3;90m
RED			= \033[0;1;3;91m
GREEN		= \033[0;1;3;92m
GREEN_L		= \033[0;1;3;36m
YELLOW		= \033[0;1;3;33m
BLUE		= \033[0;1;3;34m
# #======================================================================================

# #=================================files directories ===================================
RNDR_DIR	= randring/
UTILS_DIR	= utils/
PARSING_DIR	= parsing/
# #======================================================================================

# #================================= Files to compile ===================================
SRC_RENDER	= rerander ray_utils vectors_utils key_hook_utils 
SRC_UTILS 	= camera_utils char_utils colors_utils image_utils linked_list_utils
SRC_PARSING	= parsing check parse_env parse_objects

SRC_FILES	= 	main $(RENDER) $(UTILS) $(PARSING) error init_program

CFLAGS		= -Wall -Wextra -Werror -funroll-loops -fsanitize=address -g
# #======================================================================================

# #===================================== Standard =======================================
NAME		= miniRT

AUTHOR		= BELKARTO && OHALIM

SRC_DIR		= srcs/

OBJ_DIR		= objs/

CC			= cc 

LIBFT_PATH		=		libs/libft/

LIBFT_LIB		=		$(LIBFT_PATH)libft.a

OBJF		=	.cache_exists
# #======================================================================================


# # ===Better not to touch ===#
SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
RENDER		=	$(addprefix $(RNDR_DIR), $(addsuffix , $(SRC_RENDER)))
UTILS		=	$(addprefix $(UTILS_DIR), $(addsuffix , $(SRC_UTILS)))
PARSING		=	$(addprefix $(PARSING_DIR), $(addsuffix , $(SRC_PARSING)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
# #===========================#

all : header MAKE_LIBS $(NAME)

# # == Rule that compile source files into object files ==
$(OBJ_DIR)%.o	: $(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) $(MLX_O) -c $< -o $@
	@printf "$(GRAY)\r- Creating little RayTracer ...⌛$(NO_COLOR)"
	@sleep 0.03
	@printf "$(GRAY)\r- Creating little RayTracer ...⏳$(NO_COLOR)"
	@sleep 0.03
# #=======================================================

MAKE_LIBS	:
	@make -C $(LIBFT_PATH) all
	@echo
mlx:
	@make -C $(MLX_PATH)
	@echo


# #=== rule that compile the final program ===
$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(MLXCC) $(LIBFT_LIB) -o $(NAME)
	@printf "$(GREEN)\n- Little RayTracer is ready ✅🥳\n$(NO_COLOR)"
# #===========================================

# #=======================#

# #== rule that called if object folder doesn't exist ==
$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(RNDR_DIR)
	@mkdir -p $(OBJ_DIR)$(UTILS_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSING_DIR)
# #=====================================================

## # == rule deleting compiled files : the cache folder ==
clean : header
	@rm -rf $(OBJ_DIR)
	@make clean -C libs/libft
	@printf "$(BLUE)clean\t:\t\t\t$(GREEN)[✓]$(NO_COLOR)\n"
# # =====================================================

# # == Rule calling clean and deleting the final file ==
fclean	: header clean
	@make fclean -C libs/libft
	@rm -f $(NAME)
	@printf "$(BLUE)fclean\t:\t\t\t$(GREEN)[✓]$(NO_COLOR)\n\n"
# # ====================================================

# # == HEADER DISPLAYS AUTHOR'S NAME AND COMILER AND FLAGS BEEN USED AND ===
header:
	@echo
	@printf  "$(GREEN_L)Author\t: $(BLUE)$(AUTHOR)\n"
	@printf  "$(GREEN_L)CC    \t: $(YELLOW)$(CC)\n\033[m"
	@printf  "$(GREEN_L)Flags \t: $(YELLOW)$(CFLAGS)\n\033[m"
	@echo
# # ========================================================================
re		:	fclean all
