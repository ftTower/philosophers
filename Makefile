# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tauer <tauer@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 17:59:50 by tauer             #+#    #+#              #
#    Updated: 2024/04/29 01:03:44 by tauer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	bin
BUILD_DIR	=	build
NAME		=	philo
CFLAG		=	-Wall -Wextra -Werror -I./includes -g3

SRC			=	$(SRC_DIR)/main.c \
				$(SRC_DIR)/setup/data.c \
				$(SRC_DIR)/setup/param.c \
				$(SRC_DIR)/setup/philo.c \
				$(SRC_DIR)/setup/fork.c \
				$(SRC_DIR)/utils.c/utils.c \
				$(SRC_DIR)/utils.c/print.c \
				$(SRC_DIR)/utils.c/printer.c \
				$(SRC_DIR)/process/thread_handle.c \
			
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
