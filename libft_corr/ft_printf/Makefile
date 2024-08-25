NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 -O0

HEADERS := src/ft_printf.h

SRCS :=
TEST_SRC := test.c
SRC := $(wildcard src/*.c)
GNL := $(wildcard src/gln/*.c)

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[1;34m
COLOUR_cyan=\033[0;96m
COLOUR_Yellow=\033[0;33m
COLOUR_LightYellow=\033[0;93m
COLOUR_Default=\033[0;39m

OBJDIR := obj
OBJS :=  $(SRCS:%.c=$(OBJDIR)/%.o)
SRC_OBJS := $(SRC:%.c=$(OBJDIR)/%.o)
GNL_OBJS := $(GNL:%.c=$(OBJDIR)/%.o)
TEST_OBJS := $(TEST_SRC:%.c=$(OBJDIR)/%.o)

NEC_OBJS = $(SRC_OBJS) $(GNL_OBJS)

all: $(NAME)

$(OBJDIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "$(COLOUR_LightYellow)Compiling Printf $(COLOUR_cyan)$<$(COLOUR_Default)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(NEC_OBJS) $(OBJS)
#	@make -C src/libft bonus
#	@$(CC) $(NEC_OBJS) $(OBJS) $(CFLAGS) -Lsrc/libft -lft -o $(NAME)
#	@cp src/libft/libft.a $(NAME)
	@ar rcs $(NAME) $(NEC_OBJS) $(OBJS)

	@echo "$(COLOUR_GREEN)Compiled $@ $(COLOUR_Default)"

test: $(NEC_OBJS) $(TEST_OBJS)
#	@make -C src/libft bonus
	@$(CC) $(NEC_OBJS) $(TEST_OBJS) $(CFLAGS) -Lsrc/libft -lft -o $(NAME)
	@echo "$(COLOUR_GREEN)Compiled $@$(COLOUR_Default) with$(COLOUR_Yellow) $(TEST_SRC)$(COLOUR_Default)"

clean:
#	@make clean -C src/libft
	@rm -rf $(OBJDIR)
	@echo "$(COLOUR_RED)Cleaned Printf$(COLOUR_Default)"

fclean:
	@make clean
	@rm -f $(NAME)
#	@make fclean -C src/libft
	@echo "$(COLOUR_RED)Full Program Cleaned 'Printf'$(COLOUR_Default)"

re:
	@make fclean
	@make $(NAME)

re_test:
	@make fclean
	@make test
	

Debug: $(NEC_OBJS) $(TEST_OBJS)
	@make -C src/libft bonus
	@$(CC) $(NEC_OBJS) $(TEST_OBJS) $(CFLAGS) -Lsrc/libft -lft -o ../Debug/Debug
	@echo "$(COLOUR_Yellow)Compiled $@ at ../Debug/Debug$(COLOUR_Default)"

clean_Debug:	clean
	@rm -f ../Debug/Debug Debug


.PHONY: all clean
