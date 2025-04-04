/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:30:48 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/04 16:46:11 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "./lexer.h"

// Binary tree
enum	e_redir_type
{
	REDIR_OUT = 1,
	REDIR_APPEND_OUT,
	REDIR_IN,
	REDIR_HEREDOC,
};

enum	e_node_type
{
	NODE_CMD = 0,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
};

typedef struct s_redir {
	char			**value;
	int				redir_type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_ast
{
	char			**cmd;
	int				node_type;
	t_redir			*redir;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// Parser.c
t_ast	*parse_token(t_token *token, t_ast **node);
void	ft_handle_redir(t_redir **redir, t_token **token, t_ast **node);
// void	ft_create_tree(t_ast **root, t_token *token);
t_token	*find_last_logical_operator(t_token *token);
t_token	*find_last_pipe(t_token *token);
t_ast	*parse_pipes(t_token *token, t_ast **node);
t_ast	*parse_simple_command(t_token *token, t_ast **node);
t_token	*split_token(t_token *token, t_token *op, t_token *head, t_token *tail);
t_ast	*parse_parentheses(t_token *token, t_ast **node);

// Node_cmd.c
t_ast	*ft_create_cmd_solo(t_token *token);
t_ast	*ft_new_ast(int node_type);
t_redir	*ft_new_redir(int redir_type);

// Node.c
t_ast	*ft_create_node_mandatory(t_token *token);
t_ast	*ft_create_node_bonus(t_token *token);

// free_ast
void	ft_free_ast(t_ast **root);
void	ft_free_redir(t_redir *redir);

#endif