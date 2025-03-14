/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:29:58 by andrean           #+#    #+#             */
/*   Updated: 2025/03/14 16:51:41 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_error(char *key)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (ft_isdigit(key[i]))
		return (0);
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	if (key[i])
		return (0);
	return (1);
}

int	export_one(char *str)
{
	t_hashtable	*env;
	char		*equalsign;
	char		*key;
	char		*value;

	env = (*get_world())->env;
	if (!env)
		env = (*get_world())->new_env;
	equalsign = ft_strchr(str, '=');
	if (!equalsign)
		key = str;
	else
	{
		key = ft_substr(str, 0, equalsign - str);
		value = ft_substr(equalsign, 1, ft_strlen(equalsign + 1));
		if (!key || !value)
			;//malloc error
	}
	if (!check_key(key))
		return (export_error(key));
	if (ft_get_element(env, key))
		ft_remove_element(env, key);
	ft_add_element(env, key, value);
	return (0);
}

int	ft_export(t_ast *node)
{
	int	arg_nb;
	int	count;
	int	retval;

	retval = 0;
	arg_nb = get_arg_nb(node);
	count = 0;
	while (++count < arg_nb)
		retval += export_one(node->cmd[count]);
	if (retval)
		return (1);
	return (0);
}