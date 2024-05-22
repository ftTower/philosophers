# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tauer <tauer@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 17:59:50 by tauer             #+#    #+#              #
#    Updated: 2024/05/21 23:46:04 by tauer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	files
BUILD_DIR	=	build
NAME		=	philo
CFLAG		=	-Wall -Wextra -Werror -I./includes -g3

SRC			=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/init.c\
				$(SRC_DIR)/utils.c \
				$(SRC_DIR)/print.c \
				$(SRC_DIR)/get_set.c \
			
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
	@echo "42Paris : $(NAME)"
	@echo ""

clean : clear
	@rm -rf build/
	@echo "Clean   : *.o in build !"

fclean : clean
	@rm -f $(NAME)
	@echo "Clean   : ./$(NAME)"


re: fclean all clear 

.PHONY: all clean fclean re
