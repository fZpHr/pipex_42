# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbelle <hbelle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/05 17:52:23 by hbelle            #+#    #+#              #
#    Updated: 2024/01/17 15:16:38 by hbelle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

NAME_BONUS	=	pipex_bonus

SRCS	=	main_manda.c \
		srcs/utils/free_end.c \
		srcs/utils/error.c \
		srcs/data/found_cmd_path.c \
		srcs/parse/check_argv.c \
		srcs/utils/init.c \

SRCS_BONUS = main_bonus.c \
		srcs/utils/free_end.c \
		srcs/data/found_cmd_path_bonus.c \
		srcs/parse/check_argv.c \
		srcs/utils/error.c \
		srcs/utils/init.c \
		srcs/data/heredoc_bonus.c \

	
OBJ_DIR = .o
OBJTS = $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
OBJTS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:%.c=%.o))
LIBFT	=	libft/libft.a

COMPILE_OK = "✅"

RM	=	rm -f
HEADER =	-I includes
LIBS =	-Llibft/ -lft

CFLAGS = -Wall -Wextra -Werror -g

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@cc $(CFLAGS) $(HEADER) -c  $< -o $@
	@if test -s $*.c; then \
			echo "\033[01m\033[35m Compiling $(DEBUG)\033[00m\
			\033[36m$(SRCPATH)$*.c\033[032m  [OK] $(COMPILE_OK)\0\033[00m";\
			else \
			echo "\033[01m\033[33m Compiling $(DEBUG)\033[00m\
			\033[36m$(SRCPATH)$*.c\033[00m\  [Error]"; fi

$(NAME): $(OBJTS) $(LIBFT)
	@cc -o $(NAME) $(OBJTS) $(LIBS) $(CFLAGS) $(HEADER)
	@echo "\033[01m\033[4;33mCompilation done\033[00m\033[1;31m -->\033[00m\033[1;32m ${NAME}\033[00m"

$(LIBFT):
	@make -C libft/ -s

all:	${NAME}

bonus: $(OBJTS_BONUS) $(LIBFT)
	@cc -o $(NAME_BONUS) $(OBJTS_BONUS) $(LIBS) $(CFLAGS) $(HEADER)
	@echo "\033[01m\033[4;33mCompilation done\033[00m\033[1;31m -->\033[00m\033[1;32m ${NAME_BONUS}\033[00m"

clean:
	@${RM} -r $(OBJ_DIR) 
	@echo "\033[01m\033[31mRemoving objects ...\033[00m"
	make -C libft/ fclean -s

fclean:	clean
	@${RM} ${NAME} ${NAME_BONUS}
	@echo "\033[01m\033[31mRemoving exec : ${NAME} ...\033[00m"

re:	fclean $(LIBFT) all

.PHONY: all clean fclean re
