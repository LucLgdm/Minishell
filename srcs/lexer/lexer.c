/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:25:40 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/07 15:07:15 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*tokenization_token(char *prompt, t_token **token_lst)
{
	int		len_token;

	len_token = 0;
	while (*prompt)
	{
		if (ft_isspace(*prompt))
			prompt++;
		else if (*prompt == '(')
		{
			*token_lst = handle_parenthesis(&prompt, token_lst);
			if (!token_lst)
				return (NULL);
		}
		else
		{
			len_token = token_len(prompt);
			*token_lst = fill_token(*token_lst, prompt, len_token);
			prompt += len_token;
		}
	}
	return (*token_lst);
}

static int	ft_length_in_quote(char *ptr)
{
	int	length;
	int	quote_type;

	quote_type = -1;
	length = 1;
	if (*ptr == CHAR_S_QUOTE)
		quote_type = CHAR_S_QUOTE;
	else
		quote_type = CHAR_D_QUOTE;
	ptr++;
	while (*ptr)
	{
		length++;
		if (*ptr == quote_type)
			return (length);
		ptr++;
	}
	ft_syntaxe_error(*get_world());
	return (1);
}

int	token_len(char *input)
{
	int	length;
	int	to_add;

	length = 0;
	if ((input[0] == '<' && input[1] == '<') || (input[0] == '>'
			&& input[1] == '>') || (input[0] == '|' && input[1] == '|')
		|| (input[0] == '&' && input[1] == '&'))
		length = 2;
	else if (*input == '|' || *input == '<' || *input == '>' || *input == '&')
		length = 1;
	else
	{
		while (*input && *input != '|' && *input != '<' && *input != '>'
			&& *input != ' ' && *input != '&')
		{
			to_add = 1;
			if (*input == CHAR_S_QUOTE || *input == CHAR_D_QUOTE)
				to_add = ft_length_in_quote(input);
			length += to_add;
			input += to_add;
		}
	}
	return (length);
}
