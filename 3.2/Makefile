# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tauer <tauer@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/06 18:57:06 by tauer             #+#    #+#              #
#    Updated: 2024/06/07 17:14:04 by tauer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC_DIR		=	files
BUILD_DIR	=	build
NAME		=	philo
CFLAG		=	-Wall -Wextra -Werror -I./lib -g3

SRC			=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/init.c\
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/philos.c \
				$(SRC_DIR)/error.c \
			
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
	@valgrind -s --leak-check=full --show-leak-kinds=all  ./philo 10 200 200 200

hellgrind :
	@valgrind --tool=helgrind ./philo 10 200 200 200

re: fclean all clear 

.PHONY: all clean fclean re
