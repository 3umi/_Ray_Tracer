# #=============================== OS detecter ==================================
OS			= $(shell uname -s)
# #==============================================================================

# #============= wish flags to use to compile depending on the os ===============
ifeq ($(OS), Darwin)
	MLX_O = -I./libs/mlx_macos -c -o3
	MLXCC = -l./libs/mlx_macos/mlx -framework OpenGL -framework AppKit
else
	MLX_O = -I/usr/include -I/libs/mlx_linux -o3 -c
	MLXCC = -L/usr/lib/ -I/usr/include -I./libs/mlx_linux -lXext -lX11 -lm -lbsd
	#-L./libs/mlx_linux -llibs/mlx_linux -L/usr/lib/ -I./libs/mlx_linux -lXext -lX11 -lm
endif
# #==============================================================================

# #=================================== Colors ===================================
NO_COLOR    = \033[0m
GRAY 		= \033[0;1;3;90m
RED 		= \033[0;1;3;91m
GREEN		= \033[0;1;3;92m
GREEN_L		= \033[0;1;3;36m
YELLOW		= \033[0;1;3;33m
BLUE		= \033[0;1;3;34m
# #==============================================================================

# #================================ Standard ====================================
NAME		= minirt
SRC_DIR		= srcs/
OBJ_DIR		= obj/
LIBFT		= libs/libft/libft.a
SRC_FILES	= main
# #==============================================================================

AUTHOR		= 	belkarto && ohalim
SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
CFLAGS = -g -O3 -Wall -Wextra -Werror 
#-march=native -funroll-loops 
#-g -fsanitize=address
CC = gcc 
OBJF		=	.cache_exists


all : header $(NAME)

# #============== Rule that compile source files into object files ============
$(OBJ_DIR)%.o	: $(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(CFLAGS) $(MLX_O) $< -o $@
	@printf "$(GRAY)\rcompiling...$(NO_COLOR)"
# #==============================================================================

# #==================== rule that compile the final program =====================
$(NAME) : $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLXCC) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)\r- Fdf is ready ✅🥳 \n$(NO_COLOR)"
# #==============================================================================

# #=============================== creat bonus part =============================
$(LIBFT)	:	libs/libft
	@make -C libs/libft
# #==============================================================================


# #================== rule that called if object folder doesn't exist ===========
$(OBJF):
	@mkdir -p $(OBJ_DIR)
# #==============================================================================


# # =============== rule deleting compiled files : the cache folder =============
clean : header
	@rm -rf $(OBJ_DIR)
	@make clean -C include/my_lib
	@printf "$(RED)-->   CLEANED   <--$(NO_COLOR)"
# #==============================================================================

# # =================== Rule calling clean and deleting the final file ==========
fclean	:	clean
	@make fclean -C include/my_lib
	@rm -f $(NAME)
# #==============================================================================

re		:	fclean all

header	:
	@echo "$(GREEN)"
	@printf  "$(GREEN_L)Author\t: $(BLUE)$(AUTHOR)\n"
	@printf  "$(GREEN_L)CC    \t: $(YELLOW)$(CC)\n\033[m"
	@printf  "$(GREEN_L)Flags \t: $(YELLOW)$(CFLAGS)\n\033[m"
	@echo
	@echo "$(NO_COLOR)"
# #==============================================================================
# @echo "███████╗██████╗ ███████╗"
# @echo "██╔════╝██╔══██╗██╔════╝"
# @echo "█████╗  ██║  ██║█████╗  "
# @echo "██╔══╝  ██║  ██║██╔══╝  "
# @echo "██║     ██████╔╝██║     "
# @echo "╚═╝     ╚═════╝ ╚═╝     "
                        
