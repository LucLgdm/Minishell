# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luclgdm <luclgdm@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 10:49:30 by lde-merc          #+#    #+#              #
#    Updated: 2025/01/24 07:47:12 by luclgdm          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
SRC_DIR = srcs
OBJ_DIR = objs
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INCLUDES = includes/

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
		$(CC) $(CFLAGS) $(OBJ) -pthread -o $(NAME)
		@echo "\033[0;32mSUCCESS !\033[0m \033[0;33m$(NAME)\033[0m"
		
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;36mCleaning of the object directory\033[0m \033[0;34m$(OBJ_DIR)\033[0m"
	
fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;36mCleaning of the executable\033[0m \033[0;33m$(NAME)\033[0m"
	
re: fclean all

.PHONY: all clean fclean re