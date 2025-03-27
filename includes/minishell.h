/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:15:58 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/27 14:18:05 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "./builtins.h"
# include "./exec.h"
# include "./hashtable.h"
# include "./parsing.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include "libft_stop.h"

typedef struct s_world
{
	char		*prompt;
	int			fd[2];
	t_hashtable	*env;
	t_hashtable	*new_env;
	t_hashtable	*hidden_vars;
	t_ast		*tree;
	t_token		*tokenlist;
}	t_world;

// environement
void	prompt(t_world *world);
void	handle_signal(int sig);
void	handle_signal_afterprompt(int sig);
void	handle_signal_for_stop(int sig);
t_world	**get_world(void);

// binary_tree
void	fill_tree(t_world **world);

// free
void	free_all(t_world **world);
void	exit_process(int exit_status);
void	ft_syntaxe_error(t_world *world);

// print.c
void	print_tab(char **tab);
void	print_token(t_token *token_lst, int i);
void	print_tree(t_ast *root, int i);

// exec
int		exec_tree(t_world *world, t_ast *node);
int		exec_node(t_world *world, t_ast *node, char **paths);

// wildcards
char	**get_trnclst(char *str);
char	**manage_wildcards(char **args, int index, char **trunclst);
char	**onewildtab(void);
char	**manage_quotes(char **prev_words, char *str, int index);
char	**onelinetab(char *str);

#endif