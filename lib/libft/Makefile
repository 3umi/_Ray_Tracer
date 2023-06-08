CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
OBJEC		= 	$(SRC:.c=.o)
#----------------------------------------------#
#			  archive file name
#----------------------------------------------#
NAME		=	libft.a

#----------------------------------------------#
#				source code 
#----------------------------------------------#
SRC			=	ft_atoi.c		ft_bzero.c		\
				ft_calloc.c		ft_isalnum.c	\
				ft_isalpha.c	ft_isascii.c	\
				ft_isdigit.c	ft_isprint.c	\
				ft_memchr.c 	ft_memcmp.c		\
				ft_memcpy.c		ft_memmove.c	\
				ft_memset.c 	ft_strchr.c		\
				ft_strdup.c		ft_strlcat.c	\
				ft_strlcpy.c	ft_strlen.c 	\
				ft_strncmp.c	ft_strnstr.c	\
				ft_strrchr.c	ft_tolower.c	\
				ft_toupper.c	ft_substr.c 	\
				ft_strjoin.c	ft_strtrim.c	\
				ft_split.c		ft_itoa.c		\
				ft_strmapi.c	ft_striteri.c 	\
				ft_putchar_fd.c	ft_putstr_fd.c 	\
				ft_putendl_fd.c ft_putnbr_fd.c	\
				ft_intlen.c		ft_lstnew.c 	\
				ft_lstadd_front.c	ft_lstsize.c\
				ft_lstlast.c	ft_lstadd_back.c\
				ft_lstdelone.c	ft_lstclear.c 	\
				ft_lstiter.c	ft_lstmap.c 	\
				ft_strrev.c		ft_puthex.c		\
				ft_putuint.c	ft_putformat.c	\
				ft_printf.c		get_next_line_utils.c \
				get_next_line.c	ft_lstnew_int.c 	\
				ft_lstadd_back_int.c	ft_lstdelone_int.c\
				ft_lstclear_int.c	ft_atol.c\
				ft_lstsize_int.c	ft_strcmp.c

#----------------------------------------------#
# 					Colors
#----------------------------------------------#
NO_COLOR    = \033[0m
GRAY 		= \033[0;1;3;90m
RED 		= \033[0;1;3;91m
GREEN 		= \033[0;1;3;92m

all			: $(NAME)
#----------------------------------------------#
#		  compiling src files to object 
#----------------------------------------------#
%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(GREEN)█$(NO_COLOR)"

# @printf "\r$(GRAY)- Creating libft ...⌛$(NO_COLOR)"
# @sleep 0.03
# @printf "\r$(GRAY)- Creating libft ...⏳$(NO_COLOR)"
# @sleep 0.03
#----------------------------------------------#



#----------------------------------------------#
#				creat Archiive
#----------------------------------------------#
$(NAME)		: $(OBJEC)
	@ar rc $(NAME) $(OBJEC)
	@printf "\n\n$(GREEN)- Libft finished$(NO_COLOR) ✅🥳\n\n"
#----------------------------------------------#
#				delete object file
#----------------------------------------------#
clean		:
	@rm -f $(OBJEC)
#----------------------------------------------#
#		 delete object file and archive
#----------------------------------------------#
fclean		: clean
	@rm -f $(NAME)


#----------------------------------------------#
#			delete all and remake it
#----------------------------------------------#
re			: fclean all

.PHONY		: all clean fclean re
