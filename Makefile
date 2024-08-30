# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/04 14:31:32 by mstrauss          #+#    #+#              #
#    Updated: 2024/08/30 18:30:18 by mstrauss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= 	philosophers

MAX_THRDS = 200

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -D MAX_THREADS=$(MAX_THRDS) -g -ggdb -O2 #-Ofast -ffast-math -march=native -mtune=native -funroll-loops  # -fsanitize=address -fsanitize=undefined
RM		=	rm -rf

INC		=	-Iincludes/

SRC_DIRS =	./srcs			

vpath %.c $(SRC_DIRS)
vpath %.h includes

SRC =	good_sleep.c \
		main.c \
		philo.c \
		splash_screen.c \
		str_utils.c \
		validate_args.c \
		watcher.c \
		philo_utils.c \
		set_mut_struct.c

HEADERS = philo.h

OBJ_DIR = obj
OBJ 	= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# COLORS
BLUE		=	\033[0;34m
YELLOW		= 	\033[0;33m
GREEN		= 	\033[0;32m
NO_COLOR	=	\033[0m

all: $(NAME)

start_compile:
	@printf "$(BLUE)Compiling Philosophers...$(NO_COLOR)\n"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -lpthread $(OBJ) -o $@ $(LIB)
	@printf "$(GREEN)SUCCESS - $(NAME) has been successfully compiled$(NO_COLOR)\n"
	@printf "$(GREEN)Compiling Files: Done$(NO_COLOR)\n"

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)
	@printf "$(GREEN)Compiled $(notdir $<)$(NO_COLOR)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) $(OBJ_DIR) && printf "$(YELLOW)Removing philosophers object files...$(NO_COLOR)\n"

fclean:
	@$(RM) $(OBJ_DIR) && printf "$(YELLOW)Removing philosophers object files...$(NO_COLOR)\n"
	@$(RM) $(NAME) && printf "$(YELLOW)Removing philosophers binary$(NO_COLOR)\n"
	@printf "$(GREEN)Cleaned up $(NAME)$(NO_COLOR)\n"

re: fclean all

debug: CFLAGS += -fsanitize=address -fsanitize=undefined -DDEBUG=true
debug: re

# test:
# 	bash 42_philosophers_tester/tester.sh m

.PHONY: all test clean fclean re start_compile -DDEBUG=1