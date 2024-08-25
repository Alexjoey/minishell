# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlaverge <tlaverge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 14:50:27 by tlaverge          #+#    #+#              #
#    Updated: 2023/11/16 15:56:06 by tlaverge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_memcpy.c \
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c

BONUS			=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c

HEADERS			= libft.h

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[1;34m
COLOUR_Yellow=\033[0;33m
COLOUR_Default=\033[0;39m

OBJDIR := obj
OBJS :=  			$(SRCS:%.c=$(OBJDIR)/%.o)
BONUS_OBJS := 		$(BONUS:%.c=$(OBJDIR)/%.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I. -g3 -O0

NAME			= libft.a

all:			$(NAME)

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "$(COLOUR_Yellow)Compiling libft $(COLOUR_BLUE)$<$(COLOUR_Default)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJS)
	@make -C ft_printf
	@cp ft_printf/libftprintf.a $(NAME)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(COLOUR_GREEN)libft archive Done!$(COLOUR_Default)"


clean:
	@make clean -C ft_printf
	@echo "libft archive being cleaned..."
	@$(RM) $(OBJS) $(BONUS_OBJS)
	@rm -rf $(OBJDIR)
	@echo "$(COLOUR_Yellow)libft archive .o files did Jisatsu$(COLOUR_Default)"
	

fclean:			clean
	@make fclean -C ft_printf
	@$(RM) $(NAME)
	@echo "$(COLOUR_RED)libft .a is ded$(COLOUR_Default)"

re:				fclean bonus

bonus:			$(OBJS) $(BONUS_OBJS)
	@make -C ft_printf
	@cp ft_printf/libftprintf.a $(NAME)
	@ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(COLOUR_GREEN)libft archive + bonus Done!$(COLOUR_Default)"

.PHONY:			all clean fclean re bonus