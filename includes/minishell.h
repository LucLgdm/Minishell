/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:15:58 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/03 15:55:57 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

# include "./lexer.h"

// Binary tree
typedef struct s_node {
    char **cmd;          // Command and its arguments
    struct s_node *left;
    struct s_node *right;
    char *token;          // Operator token (|, &&, ||, ;)
    char *infile;        // Input redirection file (<)
    char *outfile;       // Output redirection file (> or >>)
    int append;          // 1 if >> is used, 0 for >
    int pipe_fd[2];      // Pipe file descriptors (used if node is a pipe)
} t_node;


typedef struct s_world
{
	char	*home;
	char	*prompt;
	t_list	*env;
	t_node	*tree;
}	t_world;




// output
void	handle_signal(int sig);

// environement
void	copy_env(t_list **env, char **envp, t_world *world);
void	prompt(t_world *world);

// taken
char    **tokenization_char(char *prompt);
int     ft_isoperator(char c);
void    ft_case_double(char *prompt, char **tmp_token, int *i);
void	ft_case_word(char *prompt, char **tmp_token, int *i);
void	process_token(char *prompt, char **tmp_token, int *i, char **token, int *j);

// taken 2
void	handle_quote(char *prompt, char **tmp_token, int *i, char **token, int *j);
// void	handle_parenthesis(char *prompt, char **tmp_token, int *i, char **token, int *j);

// parse_token
t_node	*parse_token(char **token, int *i);

// binary_tree
void	fill_tree(t_world *world);

// tree_usefull
t_node  *new_node(void);

// free
void	free_all(t_world *world);


void print_tab(char **tab);
void	print_tree(t_node *root);

#endif