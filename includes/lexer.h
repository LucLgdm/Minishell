/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:17:28 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/03 18:24:23 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

enum	e_char_type {
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_DOLLER = '$',
	CHAR_S_QUOTE = 39,
	CHAR_D_QUOTE = '"',
};

enum	e_token_type {
	TOKEN_WORD = 0,
	TOKEN_PIPE,
	TOKEN_GREATER,
	TOKEN_GREATGREATER,
	TOKEN_LESSER,
	TOKEN_LESSLESSER,
	TOKEN_PIPEPIPE,
	TOKEN_ANDAND, 
	TOKEN_PARENTHESES
};

typedef struct s_token {
	char			*value;
	int				token_type;
	struct s_token	*prev;
	struct s_token	*next;
	struct s_token	*sub_token;
}	t_token;

//	lexer.c
t_token	*tokenization_token(char *prompt);
int		token_len(char *input);

//	fill_token.c
t_token	*fill_token(t_token *token_lst, char *prompt, int len_token);
void	ft_free_token(t_token *token_lst);
t_token	*ft_create_token(int len_token, char *prompt);

//	fill_token2.c
t_token	*handle_parenthesis(char **prompt, t_token **token_lst);

#endif