# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 11:58:06 by amylle            #+#    #+#              #
#    Updated: 2024/10/21 08:48:24 by amylle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR	= ./src
INC_DIR	= ./inc
OBJ_DIR	= ./obj

SRCS	= main.c src/executor/executor.c ./src/builtins/echo_builtin.c ./src/builtins/cd_builtin.c \
		  ./src/builtins/pwd_builtin.c ./src/builtins/do_builtin.c ./src/builtins/env_builtin.c \
		  ./src/builtins/exit_builtin.c ./src/Parser/parser_utils1.c ./src/Parser/parser.c \
		  ./src/Parser/struct_filler.c ./src/Parser/Struct_init.c ./src/executor/signals.c \
		  ./src/builtins/unset_builtin.c ./src/builtins/export_builtin.c ./src/Parser/expand_dollarsigns.c\
		  ./src/executor/redirections.c ./src/executor/executor_utils.c ./src/executor/signals2.c

#SRCS	= $(wildcard src/*.c) #$(wildcard src/*.h)
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -g3 -O0
INCLUDE	= -I$(SRC_DIR) -Llibft -lft -lreadline -lncurses 
#INCLUDE		= $(wildcard src/*.h)
LIBFT	= libft/libft.a
RM		= rm -rf

NAME	= minishell

#---------------------------Messages--------------------------------------------

BOLD_PURPLE	=	\033[1;35m

BOLD_CYAN	=	\033[1;36m

BOLD_YELLOW	=	\033[1;33m

NO_COLOR	=	\033[0m


all:	$(NAME)


$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -Iinc -c $< -o $@ 

$(LIBFT):
		@make -C ./libft

$(NAME):	$(OBJS) $(LIBFT)
				@echo Compiling $(NAME)
				@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o $(NAME)
				@make clean -C ./libft

re:			fclean all

clean:	
				@echo "$(BOLD_YELLOW)Removing all object files and directories"
				$(RM) $(OBJ_DIR)
				@make fclean -C ./libft

fclean:
				@echo "$(BOLD_YELLOW)Removing binaries"
				$(RM) $(NAME) $(OBJ_DIR)
				@make fclean -C ./libft

Debug:		$(OBJS) $(LIBFT)
				@echo Compiling $(NAME)
				@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) -o ../Debug/Debug
				$(RM) $(NAME) $(OBJ_DIR)
				@make fclean -C ./libft

re:			fclean all
