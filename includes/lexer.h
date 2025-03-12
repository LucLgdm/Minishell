/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:17:28 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/12 17:00:44 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "./hashtable.h"

enum	e_char_type
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_DOLLAR = '$',
	CHAR_S_QUOTE = '\'',
	CHAR_D_QUOTE = '"',
};

enum	e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_PIPE,
	TOKEN_ANDAND,
	TOKEN_PIPEPIPE,
	TOKEN_PARENTHESES,
	TOKEN_GREATER,
	TOKEN_GREATGREATER,
	TOKEN_LESSER,
	TOKEN_LESSLESSER
};

typedef struct s_token {
	char			*value;
	int				token_type;
	int				created;
	struct s_token	*prev;
	struct s_token	*next;
	struct s_token	*sub_token;
}	t_token;

//	lexer.c
t_token	*tokenization_token(char *prompt);
int		token_len(char *input);

//	fill_token.c
t_token	*fill_token(t_token *token_lst, char *prompt, int len_token);
t_token	*ft_create_token(int len_token, char *prompt);

//	fill_token2.c
t_token	*handle_parenthesis(char **prompt, t_token **token_lst);

//	dollar.c
int		handle_dollar(t_token **token_lst, t_hashtable *env_ht);
char	*ft_expand(char *word, t_hashtable *env_ht);
void	ft_single_quote(char **new_word, char *word, int *i);
void	ft_double_quote(char **new_word, char *word, int *i,
			t_hashtable *env_ht);
char	*ft_get_env_value(char *key, t_hashtable *env_ht);
char	*ft_extract_var_name(char *str, int *i);
void	ft_append_char(char **new_word, char c);
void	ft_replace(char **new_word, char *word, int *i, t_hashtable *env_ht);

void	ft_free_token(t_token *token);

#endif