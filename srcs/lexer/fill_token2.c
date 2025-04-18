/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:48:26 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/07 14:55:29 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*handle_parenthesis(char **prompt, t_token **token_lst)
{
	int		p_count;
	int		i;
	char	*sub_prompt;
	t_token	*tmp;

	p_count = 1;
	i = 0;
	while ((*prompt)[++i] && p_count > 0)
	{
		if ((*prompt)[i] == '(')
			p_count++;
		else if ((*prompt)[i] == ')')
			p_count--;
	}
	if (p_count != 0)
		ft_syntaxe_error(*get_world());
	sub_prompt = ft_substr_stop(*prompt, 1, i - 2);
	(*token_lst) = fill_token(*token_lst, "(", 1);
	tmp = *token_lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->sub_token = tokenization_token(sub_prompt, &tmp->sub_token);
	free(sub_prompt);
	*prompt += i;
	return (*token_lst);
}
