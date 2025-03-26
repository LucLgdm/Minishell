# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 12:51:11 by lde-merc          #+#    #+#              #
#    Updated: 2025/03/26 12:22:34 by lde-merc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
AR = ar -rcs

SRC_DIR = srcs
OBJ_DIR = obj
FILES = $(wildcard $(SRC_DIR)/*.c)
HEADER = libft.h
OBJ = $(FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;31mSuppression des objets libft\033[0m"
	
fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;31mSuppression de la libft\033[0m"
	
re: fclean all

.PHONY: all clean fclean re
