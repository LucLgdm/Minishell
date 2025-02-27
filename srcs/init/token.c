/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:57:50 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/27 16:39:35 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenization(char *prompt)
{
	char	**token;
	char	*tmp_token;
	int		i;
	int		j;

	token = ft_calloc(100, sizeof(char *));
	tmp_token = ft_calloc(256, sizeof(char));
	if (!token || !tmp_token)
		return (NULL);
	i = 0;
	j = 0;
	while (prompt[i])
	{
		while (ft_isspace(prompt[i]))
			i++;
		handle_parenthesis(prompt, &tmp_token, &i, token, &j);
		handle_quote(prompt, &tmp_token, &i, token, &j);
		process_token(prompt, &tmp_token, &i, token, &j);
	}
	token[j] = NULL;
	free(tmp_token);
	return (token);
}

void	process_token(char *prompt, char **tmp_token, int *i, char **token,
		int *j)
{
	if (ft_isoperator(prompt[*i]))
	{
		if (prompt[*i] == '<' || prompt[*i] == '>' || prompt[*i] == '|'
			|| prompt[*i] == '&')
		{
			ft_case_double(prompt, tmp_token, i);
			token[(*j)++] = ft_strdup(*tmp_token);
		}
		else
		{
			(*tmp_token)[0] = prompt[*i];
			(*tmp_token)[1] = 0;
			(*i)++;
			token[(*j)++] = ft_strdup(*tmp_token);
		}
	}
	else if (prompt[*i])
	{
		ft_case_word(prompt, tmp_token, i);
		if (prompt[*i - 1] && prompt[*i - 1] != '"' && prompt[*i - 1] != '\''
			&& prompt[*i - 1] != ')')
			token[(*j)++] = ft_strdup(*tmp_token);
	}
}

int	ft_isoperator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '(' || c == ')' || c == '<'
		|| c == '>');
}

void	ft_case_double(char *prompt, char **tmp_token, int *i)
{
	(*tmp_token)[0] = prompt[*i];
	(*tmp_token)[1] = 0;
	if (prompt[*i + 1] == prompt[*i])
	{
		(*tmp_token)[1] = prompt[*i + 1];
		(*tmp_token)[2] = 0;
		(*i)++;
	}
	(*i)++;
}

void	ft_case_word(char *prompt, char **tmp_token, int *i)
{
	int	j;

	j = 0;
	while (prompt[*i] && !ft_isoperator(prompt[*i]) && !ft_isspace(prompt[*i]))
	{
		(*tmp_token)[j] = prompt[*i];
		j++;
		(*i)++;
	}
	(*tmp_token)[j] = '\0';
}
