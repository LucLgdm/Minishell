/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/27 14:17:39 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	ft_is_operator(t_token *token)
{
	int	type;

	type = token->token_type;
	return (type == TOKEN_ANDAND || type == TOKEN_PIPE
		|| type == TOKEN_PIPEPIPE);
}

static bool	ft_is_redir(t_token *token)
{
	int	type;

	type = token->token_type;
	return (type == TOKEN_GREATER || type == TOKEN_GREATGREATER
		|| type == TOKEN_LESSER || type == TOKEN_LESSLESSER);
}

static bool	ft_check_syntaxe(t_token *token_lst)
{
	if (ft_is_operator(token_lst))
		return (false);
	while (token_lst->next)
	{
		if (ft_is_operator(token_lst) && ft_is_operator(token_lst->next))
			return (false);
		if (ft_is_redir(token_lst) && token_lst->next->token_type != TOKEN_WORD)
			return (false);
		if (token_lst->token_type == TOKEN_PARENTHESES)
			if (!ft_check_syntaxe(token_lst->sub_token))
				return (false);
		token_lst = token_lst->next;
	}
	if (ft_is_operator(token_lst) || ft_is_redir(token_lst))
		return (false);
	return (true);
}

void	ft_syntaxe_error(t_world *world)
{
	ft_putstr_fd("Syntax error\n", 2);
	ft_free_token(&world->tokenlist, 1);
	free(world->prompt);
	prompt(world);
}

void	fill_tree(t_world **world)
{
	t_token	*token_lst;

	token_lst = tokenization_token((*world)->prompt);
	if (!token_lst)
		return ;
	(*world)->tokenlist = token_lst;
	if (!ft_check_syntaxe((*world)->tokenlist))
		ft_syntaxe_error(*world);
	(*world)->tree = parse_token(token_lst);
}
