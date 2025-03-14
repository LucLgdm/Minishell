# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: andrean <andrean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 10:49:30 by lde-merc          #+#    #+#              #
#    Updated: 2025/03/14 15:26:52 by andrean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

vpath %.c srcs

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -I $(INCLUDES)
FLAGS = -lreadline $(LIBFT)

LIBFT = libft/libft.a
INCLUDES = includes/
OBJ_DIR = objs/
EXEC_DIR = exec/
INIT_DIR = init/
FREE_DIR = free/
LEXER_DIR = lexer/
HASHTABLE_DIR = hashtable/
PARSING_DIR = parsing/
BUILTIN_DIR = builtins/

# Liste des fichiers source
SRC_FILES = main.c \
			$(INIT_DIR)environement.c \
			$(INIT_DIR)binary_tree.c \
			$(INIT_DIR)print.c \
			$(INIT_DIR)parse_token.c \
			$(FREE_DIR)free.c \
			$(FREE_DIR)ft_free_ast.c \
			$(FREE_DIR)ft_free_token.c \
			$(LEXER_DIR)lexer.c \
			$(LEXER_DIR)fill_token.c \
			$(LEXER_DIR)fill_token2.c \
			$(LEXER_DIR)dollar.c \
			$(HASHTABLE_DIR)hashtable_creation.c \
			$(HASHTABLE_DIR)operation.c \
			$(HASHTABLE_DIR)ft_free_hasht.c \
			$(PARSING_DIR)parser.c \
			$(PARSING_DIR)node.c \
			$(PARSING_DIR)node_cmd.c\
			$(EXEC_DIR)exec_utils.c\
			$(EXEC_DIR)exec.c\
			$(EXEC_DIR)redirect.c\
			$(BUILTIN_DIR)builtins_utils.c\
			$(BUILTIN_DIR)cd.c\
			$(BUILTIN_DIR)echo.c\
			$(BUILTIN_DIR)exit.c\
			$(BUILTIN_DIR)export.c\
			$(BUILTIN_DIR)pwd.c\
			$(BUILTIN_DIR)unset.c\
			$(BUILTIN_DIR)env.c


# Transforme chaque fichier source en un fichier objet dans $(OBJ_DIR)
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

all: mkdir_obj $(NAME)

# Compilation des fichiers .c en .o dans le dossier $(OBJ_DIR)
$(OBJ_DIR)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Création du dossier objs/ s'il n'existe pas
mkdir_obj:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(OUTPUT_DIR)
	@mkdir -p $(OBJ_DIR)$(EXEC_DIR)
	@mkdir -p $(OBJ_DIR)$(INIT_DIR)
	@mkdir -p $(OBJ_DIR)$(FREE_DIR)
	@mkdir -p $(OBJ_DIR)$(LEXER_DIR)
	@mkdir -p $(OBJ_DIR)$(HASHTABLE_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSING_DIR)
	@mkdir -p $(OBJ_DIR)$(BUILTIN_DIR)

# Compilation finale
$(NAME): $(OBJS)
	@echo "\033[32mlibft en cours\033[0m"
	@make -C libft all --silent
	@echo "\033[0;32mSUCCESS !\033[0m \033[0;33mlibft\033[0m"
	@make -C libft clean --silent
	@echo "\033[32mCompilation minishell en cours\033[0m"
	@$(CC) $(OBJS) $(FLAGS) -o $(NAME)
	@echo "\033[0;32mSUCCESS !\033[0m \033[0;33m$(NAME)\033[0m"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;34mSuppression des objets\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;34mSuppression de l'executable $(NAME)\033[0m"

re: fclean all

val: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)
	

.PHONY: all clean fclean re