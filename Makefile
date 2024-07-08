# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tauer <tauer@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 17:59:50 by tauer             #+#    #+#              #
#    Updated: 2024/06/12 00:11:57 by tauer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	files
BUILD_DIR	=	build
NAME		=	philo
CFLAG		=	-Wall -Wextra -Werror -I./includes -g3

SRC			=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/init.c\
				$(SRC_DIR)/bool.c \
				$(SRC_DIR)/mutex.c \
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/print.c \
				$(SRC_DIR)/printer.c \
				$(SRC_DIR)/getter.c \
				$(SRC_DIR)/setter.c \
				$(SRC_DIR)/monitor.c \
				$(SRC_DIR)/philos.c \
				$(SRC_DIR)/debug.c \
				$(SRC_DIR)/printf/ft_printf.c \
				$(SRC_DIR)/printf/print_functions.c \
				$(SRC_DIR)/printf/print_functions2.c \
				$(SRC_DIR)/printf/utils.c \
			
CC			=	cc 

OBJ		=	$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, $(SRC))


$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC)	$(CFLAG)	-c	$< -o	$@
	@clear
	
all: $(NAME)

$(NAME):$(OBJ)
	@echo $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) $(CFLAG)
	@clear

clear :
	@clear
	@echo "42 - PARIS : $(NAME)"
	@echo ""

clean : clear
	@rm -rf build/
	@echo "Clean   : ./$(BUILD_DIR) !"

fclean : clean
	@rm -f $(NAME)
	@echo "Clean   : ./$(NAME)"

test : 
	@valgrind -s --leak-check=full --show-leak-kinds=all  ./philo 10 200 200 200 10

hellgrind :
	@valgrind --tool=helgrind ./philo 11 500 500 500 10

re: fclean all clear 

.PHONY: all clean fclean re
