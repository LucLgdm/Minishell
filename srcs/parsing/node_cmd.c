/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:26:16 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/06 12:41:37 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_ast	*ft_create_cmd_solo(t_token *token)
{
	t_ast	*root;
	t_token	*tmp;
	int		i;

	tmp = token;
	root = ft_new_ast(NODE_CMD, 0);
	if (root)
	{
		i = 0;
		while (tmp && (tmp->token_type == TOKEN_WORD))
		{
			root->cmd[i++] = ft_strdup(tmp->value);
			tmp->created = 1;
			tmp = tmp->next;
		}
		root->cmd[i] = NULL;
	}
	return (root);
}

t_ast	*ft_new_ast(int node_type, int redir_type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->cmd = malloc(2 * sizeof(char *));
	if (!new->cmd)
		return (NULL);
	new->cmd[0] = malloc(sizeof(char *));
	new->cmd[1] = malloc(sizeof(char *));
	if (!new->cmd[0] || !new->cmd[1])
		return (NULL);
	new->node_type = node_type;
	if (!redir_type)
		new->redir = NULL;
	else
		new->redir = ft_new_redir(redir_type);
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_redir	*ft_new_redir(int redir_type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->value = NULL;
	new->redir_type = redir_type;
	new->next = NULL;
	return (new);
}
