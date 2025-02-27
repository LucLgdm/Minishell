/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:57:50 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/27 12:42:32 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tokenization(char *prompt)
{
    char	**token;
    char	*ttoken;
    int		i;
    int		j;

    token = ft_calloc(100, sizeof(char *));
    ttoken = ft_calloc(256, sizeof(char));
    if (!token || !ttoken)
        return (NULL);
    i = -1;
    j = -1;
    while (prompt[++i])
    {
        while (ft_isspace(prompt[i]))
            i++;
        if (prompt[i] == '\0')
            break;
        process_token(prompt, &ttoken, &i, token, &j);
    }
    if (ttoken[0] != '\0')
        token[++j] = ft_strdup(ttoken);
    token[j] = NULL;
    free(ttoken);
    return (token);
}

void	process_token(char *prompt, char **ttoken, int *i, char **token, int *j)
{
    if (ft_isoperator(prompt[*i]))
    {
        if (prompt[*i] == '<' || prompt[*i] == '>' || prompt[*i] == '|'
            || prompt[*i] == '&')
        {
            ft_case_double(prompt, ttoken, i);
            token[++(*j)] = ft_strdup(*ttoken);
        }
        else
        {
            (*ttoken)[0] = prompt[*i];
            (*ttoken)[1] = 0;
            (*i)++;
        }
    }
    else
    {
        ft_case_word(prompt, ttoken, i);
        token[++(*j)] = ft_strdup(*ttoken);
    }
}

int	ft_isoperator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '(' || c == ')' || c == '<'
		|| c == '>');
}

void	ft_case_double(char *prompt, char **ttoken, int *i)
{
	(*ttoken)[0] = prompt[*i];
	(*ttoken)[1] = 0;
	if (prompt[*i + 1] == prompt[*i])
	{
		(*ttoken)[1] = prompt[*i + 1];
		(*ttoken)[2] = 0;
		(*i)++;
	}
	(*i)++;
}

void	ft_case_word(char *prompt, char **ttoken, int *i)
{
	int	j;

	j = 0;
	while (prompt[*i] && !ft_isoperator(prompt[*i]) && !ft_isspace(prompt[*i]))
	{
		(*ttoken)[j] = prompt[*i];
		j++;
		(*i)++;
	}
	(*ttoken)[j] = '\0';
}
