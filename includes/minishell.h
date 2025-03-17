/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:15:58 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/17 17:23:48 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "./builtins.h"
# include "./exec.h"
# include "./hashtable.h"
# include "./parsing.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>

extern int		g_stop;

typedef struct s_world
{
	char		*prompt;
	t_hashtable	*env;
	t_hashtable	*new_env;
	t_hashtable	*hidden_vars;
	t_ast		*tree;
	t_token		*tokenlist;
}	t_world;

// environement
void		prompt(t_world *world);
void		handle_signal(int sig);
int			ft_stop(void);
t_world		**get_world(void);
t_hashtable	*ft_create_env_hashtable(char **env);
t_hashtable	*ft_create_hidden(void);
t_hashtable	*ft_create_new_env(void);
void		ft_env_to_hashtable(char **env, t_hashtable *env_hastable);

// taken
// char		**tokenization_char(char *prompt);
// int			ft_isoperator(char c);
// void		ft_case_double(char *prompt, char **tmp_token, int *i);
// void		ft_case_word(char *prompt, char **tmp_token, int *i);
// void		process_token(char *prompt, char **tmp_token, int *i,
// 				char **token, int *j);

// taken 2
// void		handle_quote(char *prompt, char **tmp_token, int *i,
// 			char **token, int *j);

// binary_tree
void		fill_tree(t_world *world);

// free
void		free_all(t_world *world);

// print.c
void		print_tab(char **tab);
void		print_token(t_token *token_lst, int i);
void		print_tree(t_ast *root, int i);

// exec
int			exec_tree(t_world *world, t_ast *node);
int			exec_node(t_world *world, t_ast *node, char **paths);

//wildcards
char	**manage_wildcards(char **args, char *str, int index);

#endif