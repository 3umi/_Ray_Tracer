# #================================== OS detecter ==============================
OS			= $(shell uname -s)
# #=============================================================================

# #=============== wish flags to use to compile depending on the os ============
ifeq ($(OS), Darwin)
	MLXCC		= -L $(LIB)minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit 
	MLX_PATH	= mlx
else
	MLXCC		= -L $(LIB)linux -lmlx -lm -lX11 -lXext -lpthread
	MLX_PATH	= linux
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
SRC_BONUS_DIR	= srcs_bonus/
OBJ_BONUS_DIR	= objs_bonus/
RNDR_DIR	= randring/
UTILS_DIR	= utils/
PARSING_DIR	= parsing/
# #======================================================================================

# #================================= Files to compile ===================================
SRC_BONUS_FILES		=	main_bonus $(RENDER_BONUS) $(UTILS_BONUS) $(PARSING_BONUS) \
						error_bonus init_program_bonus
SRC_BONUS_RENDER	=	rerander_bonus hittable_bonus key_hook_utils_bonus sphere_bonus \
						plane_bonus cylinder_bonus triangle_bonus
SRC_BONUS_UTILS 	=	camera_utils_bonus char_utils_bonus colors_utils_bonus \
						image_utils_bonus linked_list_utils_bonus light_utils_bonus \
						ray_utils_bonus matrix_utils_bonus vectors_utils_bonus \
						vectors_utils_2_bonus mouse_utils_bonus

SRC_BONUS_PARSING	=	parsing_bonus check_bonus parse_env_bonus parse_objects_bonus \
						parse_data_bonus
# #======================================================================================
CFLAGS				=	-Wall -Wextra -Werror -funroll-loops 
#-g -fsanitize=address
# #======================================================================================

# #===================================== Standard =======================================
NAME_BONUS		= miniRT_bonus

LIB				= libs/

AUTHOR			= BELKARTO && OHALIM

CC			= cc 

LIBFT_PATH	= $(LIB)/libft/

LIBFT_LIB	= $(LIBFT_PATH)libft.a

OBJF_BONUS	=	.cache_exists_bonus
# #======================================================================================


# # ===Better not to touch ===#
SRC_BONUS	= 	$(addprefix $(SRC_BONUS_DIR), $(addsuffix .c, $(SRC_BONUS_FILES)))
OBJ_BONUS	= 	$(addprefix $(OBJ_BONUS_DIR), $(addsuffix .o, $(SRC_BONUS_FILES)))
RENDER_BONUS=	$(addprefix $(RNDR_DIR), $(addsuffix , $(SRC_BONUS_RENDER)))
UTILS_BONUS	=	$(addprefix $(UTILS_DIR), $(addsuffix , $(SRC_BONUS_UTILS)))
PARSING_BONUS=	$(addprefix $(PARSING_DIR), $(addsuffix , $(SRC_BONUS_PARSING)))
# #===========================#

all :

bonus : header MAKE_LIBS $(NAME_BONUS)

# # == Rule that compile source files into object files ==
$(OBJ_BONUS_DIR)%.o	: $(SRC_BONUS_DIR)%.c | $(OBJF_BONUS)
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
	@make -C $(LIB)/$(MLX_PATH)
	@echo


# #=== rule that compile the final program ===
$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(MLXCC) $(LIBFT_LIB) -o $(NAME)
	@printf "$(GREEN)\n- Little RayTracer is ready ✅🥳\n$(NO_COLOR)"
# #===========================================
$(NAME_BONUS) : $(OBJ_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLXCC) $(LIBFT_LIB) -o $(NAME_BONUS)
	@printf "$(GREEN)\n- Little RayTracer is ready ✅🥳\n$(NO_COLOR)"

# #=============================================================================#

# #== rule that called if object folder doesn't exist ==
$(OBJF_BONUS):
	@mkdir -p $(OBJ_BONUS_DIR)
	@mkdir -p $(OBJ_BONUS_DIR)$(RNDR_DIR)
	@mkdir -p $(OBJ_BONUS_DIR)$(UTILS_DIR)
	@mkdir -p $(OBJ_BONUS_DIR)$(PARSING_DIR)
# #=====================================================

## # == rule deleting compiled files : the cache folder ==
clean : header
	@rm -rf $(OBJ_BONUS_DIR)
	@printf "$(BLUE)clean\t:\t\t\t$(GREEN)[✓]$(NO_COLOR)\n"

# @make clean -C libs/libft
# # =====================================================

# # == Rule calling clean and deleting the final file ==
# @make fclean -C libs/libft
fclean	: header clean
	@rm -f $(NAME_BONUS)
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
re		:	fclean bonus
