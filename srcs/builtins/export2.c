/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 10:52:01 by andrean           #+#    #+#             */
/*   Updated: 2025/04/04 11:46:49 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_key_value(char **key, char **value, char *equalsign, char *str)
{
	*key = ft_substr(str, 0, equalsign - str);
	*value = ft_substr(equalsign, 1, ft_strlen(equalsign + 1));
	if (!(*value) || !(*key))
	{
		safe_free(*key);
		*key = NULL;
		safe_free(*value);
		*value = NULL;
	}
}
