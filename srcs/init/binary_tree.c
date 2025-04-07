/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/07 15:09:57 by lde-merc         ###   ########.fr       */
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

bool	ft_is_redir(t_token *token)
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
	if (!token_lst->next && token_lst->token_type == TOKEN_PARENTHESES)
		if (!ft_check_syntaxe(token_lst->sub_token))
			return (false);
	while (token_lst->next)
	{
		if (ft_is_operator(token_lst) && ft_is_operator(token_lst->next))
			return (false);
		if (ft_is_redir(token_lst) && token_lst->next->token_type != TOKEN_WORD)
			return (false);
		if (token_lst->token_type == TOKEN_PARENTHESES
			&& !(ft_is_operator(token_lst->next)
				|| ft_is_redir(token_lst->next)))
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
	ft_modify_value(world->hidden_vars, "?", "2", 0);
	ft_free_token(&world->tokenlist, 1);
	ft_free_ast(&world->tree);
	free(world->prompt);
	prompt(world);
}

void	fill_tree(t_world **world)
{
	t_token	**token_lst;

	token_lst = &(*world)->tokenlist;
	*token_lst = tokenization_token((*world)->prompt, token_lst);
	if (!*token_lst)
		return ;
	if (!ft_check_syntaxe((*world)->tokenlist))
		ft_syntaxe_error(*world);
	(*world)->tree = parse_token(*token_lst, &(*world)->tree);
}
