# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andrean <andrean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 10:49:30 by lde-merc          #+#    #+#              #
#    Updated: 2025/02/20 14:02:54 by andrean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -I $(INCLUDES)
FLAGS = -lreadline $(LIBFT)

LIBFT = libft/libft.a
INCLUDES = includes/
SRC_DIR = srcs/
OBJ_DIR = objs/
OUTPUT_DIR = output/
PARSE_DIR = parsing/
EXEC_DIR = exec/
# Liste des fichiers source
SRC_FILES = main.c \
			$(OUTPUT_DIR)prompt.c\
			$(PARSE_DIR)parsing.c\
			$(PARSE_DIR)parse_utils.c\
			$(PARSE_DIR)lst_utils.c\

# Transforme chaque fichier source en un fichier objet dans $(OBJ_DIR)
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: mkdir_obj $(NAME)

# Compilation des fichiers .c en .o dans le dossier $(OBJ_DIR)
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier objs/ s'il n'existe pas
mkdir_obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(OUTPUT_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSE_DIR)
	@mkdir -p $(OBJ_DIR)$(EXEC_DIR)

# Compilation finale
$(NAME): $(OBJS)
	@echo "\033[32mlibft en cours\033[0m"
	@make -C libft all --silent
	@echo "\033[0;32mSUCCESS !\033[0m \033[0;33mlibft\033[0m"
	@echo "\033[32mCompilation minishell en cours\033[0m"
	@$(CC) $(OBJS) $(FLAGS) -o $(NAME)
	@echo "\033[0;32mSUCCESS !\033[0m \033[0;33m$(NAME)\033[0m"

clean:
	@make -C libft clean
	@echo "\033[0;34mSuppression des objets de la libft\033[0m"
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;34mSuppression des objets\033[0m"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean --silent
	@echo "\033[0;34mSuppression de l'executable $(NAME) et de la libft.\033[0m"

re: fclean all

	

.PHONY: all clean fclean re