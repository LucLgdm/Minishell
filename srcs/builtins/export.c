/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:29:58 by andrean           #+#    #+#             */
/*   Updated: 2025/04/09 12:24:24 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_error(char *key)
{
	if (!key)
		return (-1);
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (!key || !*key)
		return (1);
	if (ft_isdigit(key[i]))
		return (1);
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	if (key[i])
		return (1);
	return (0);
}

static void	delete_quotes(char *value)
{
	int	i;
	int	n;

	if (value[0] == '"')
	{
		n = ft_strlen(value);
		i = 1;
		while (i < n)
		{
			value[i - 1] = value[i];
			i++;
		}
		value[n - 2] = '\0';
	}
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
	value = NULL;
	if (!equalsign)
		key = ft_strdup(str);
	else
		get_key_value(&key, &value, equalsign, str);
	if (check_key(key))
		return (export_error(key));
	if (ft_get_element(env, key))
		env = ft_remove_element(env, key);
	if (equalsign)
		delete_quotes(value);
	env = ft_add_element(&env, key, value);
	if (!env)
		return (safe_free(key), safe_free(value), -1);
	return (safe_free(key), safe_free(value), 0);
}

int	ft_export(t_ast *node)
{
	int	arg_nb;
	int	count;
	int	retval;
	int	error;

	error = 0;
	arg_nb = get_arg_nb(node);
	if (arg_nb == 1)
	{
		ft_print_export((*get_world())->env);
		return (0);
	}
	count = 0;
	while (++count < arg_nb)
	{
		retval = export_one(node->cmd[count]);
		if (retval == -1)
			return (retval);
		error += retval;
	}
	if (error)
		return (1);
	return (0);
}
