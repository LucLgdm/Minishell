/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:59:16 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 08:34:12 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_get_token_type(char *value)
{
	if (ft_strncmp(value, "|", 2) == 0)
		return (TOKEN_PIPE);
	else if (ft_strncmp(value, ">", 2) == 0)
		return (TOKEN_GREATER);
	else if (ft_strncmp(value, ">>", 3) == 0)
		return (TOKEN_GREATGREATER);
	else if (ft_strncmp(value, "<", 2) == 0)
		return (TOKEN_LESSER);
	else if (ft_strncmp(value, "<<", 3) == 0)
		return (TOKEN_LESSLESSER);
	else if (ft_strncmp(value, "||", 3) == 0)
		return (TOKEN_PIPEPIPE);
	else if (ft_strncmp(value, "&&", 3) == 0)
		return (TOKEN_ANDAND);
	else if (ft_strncmp(value, "(", 2) == 0)
		return (TOKEN_PARENTHESES);
	else
		return (TOKEN_WORD);
}

t_token	*ft_create_token(int len_token, char *prompt)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_substr(prompt, 0, len_token);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->token_type = ft_get_token_type(new_token->value);
	new_token->prev = NULL;
	new_token->next = NULL;
	new_token->sub_token = NULL;
	return (new_token);
}

t_token	*fill_token(t_token *token_lst, char *prompt, int len_token)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = ft_create_token(len_token, prompt);
	if (!new_token)
	{
		if (token_lst)
			ft_free_token(token_lst);
		return (NULL);
	}
	if (!token_lst)
	{
		token_lst = new_token;
		token_lst->prev = NULL;
	}
	else
	{
		tmp = token_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
	}
	return (token_lst);
}
