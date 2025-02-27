/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:00:59 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/27 14:49:43 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quote(char *prompt, char **tmp_token, int *i, char **token, int *j)
{
	char	quote_char;
	int		k;

	if (prompt[*i] == '"' || prompt[*i] == '\'')
	{
		quote_char = prompt[*i];
		(*tmp_token)[0] = quote_char;
		k = 1;
		(*i)++;
		while (prompt[*i] && prompt[*i] != quote_char)
		{
			(*tmp_token)[k++] = prompt[*i];
			(*i)++;
		}
		if (prompt[*i] == quote_char)
		{
			(*tmp_token)[k++] = quote_char;
			(*i)++;
		}
		(*tmp_token)[k] = '\0';
		token[(*j)++] = ft_strdup(*tmp_token);
	}
}

void	handle_parenthesis(char *prompt, char **tmp_token, int *i, char **token, int *j)
{
	char	parenthesis_char;
	int		k;
	int		p_count;

	p_count = 0;
	if (prompt[*i] == '(')
	{
		p_count = 1;
		parenthesis_char = prompt[*i];
		(*tmp_token)[0] = parenthesis_char;
		k = 1;
		(*i)++;
		while (prompt[*i] && p_count > 0)
		{
			(*tmp_token)[k++] = prompt[*i];
			if (prompt[*i] == parenthesis_char)
				p_count++;
			if (prompt[*i] == ')')
				p_count--;
			(*i)++;
		}
		(*tmp_token)[k] = '\0';
		token[(*j)++] = ft_strdup(*tmp_token);
		printf("i = %d\n", *i);
	}
}
