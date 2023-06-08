# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohalim <ohalim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 18:07:54 by ohalim            #+#    #+#              #
#    Updated: 2023/06/08 18:43:48 by ohalim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# #=== Colors ===
NO_COLOR	= \033[0m
GRAY		= \033[0;1;3;90m
RED			= \033[0;1;3;91m
GREEN		= \033[0;1;3;92m
GREEN_L		= \033[0;1;3;36m
YELLOW		= \033[0;1;3;33m
BLUE		= \033[0;1;3;34m
# #==============

UP				=		"\033[A"
CUT				=		"\033[K"


# #=== Standard ===
NAME		= miniRT

AUTHOR		= BELKARTO && OHALIM

SRC_DIR		= srcs/

OBJ_DIR		= objs/



LIBFT_PATH		=		libs/libft/

LIBFT_LIB		=		$(LIBFT_PATH)libft.a

MLX_PATH		=		mlx/

MLX_LIB			=		$(MLX_PATH)libmlx.a	


MLX_FLAGS		=		-Lmlx -lmlx -framework OpenGL -framework AppKit


SRC_FILES	= main

CFLAGS		= -Wall -Wextra -Werror -g
#-fsanitize=address

CC			= cc 

OBJF		=	.cache_exists
# #================

# # ===Better not to touch ===#
SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
# #===========================#

all : header MAKE_LIBS $(NAME)

# # == Rule that compile source files into object files ==
$(OBJ_DIR)%.o	: $(SRC_DIR)%.c | $(OBJF)
	$(CC) $(CFLAGS) -Imlx -c $< -o $@
	@printf $(UP)$(CUT)
	@printf "$(GRAY)\r- Creating little RayTracer ...⌛$(NO_COLOR)"
	@sleep 0.03
	@printf "$(GRAY)\r- Creating little RayTracer ...⏳$(NO_COLOR)"
	@sleep 0.03
# #=======================================================

MAKE_LIBS	:
				@make -C $(LIBFT_PATH) all
				@echo
				@make -C $(MLX_PATH) all
				@echo


# #=== rule that compile the final program ===
$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(MLX_LIB) $(LIBFT_LIB) -o $(NAME)
	@printf "$(GREEN)\n- Little RayTracer is ready ✅🥳\n$(NO_COLOR)"
# #===========================================
# stty -echoctl
# #=======================
#
# #== rule that called if object folder doesn't exist ==
$(OBJF):
	@mkdir -p $(OBJ_DIR)
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