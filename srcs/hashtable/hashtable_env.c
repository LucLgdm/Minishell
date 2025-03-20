/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:30:52 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 11:55:54 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_to_hashtable(char **env, t_hashtable *env_hastable)
{
	int		i;
	char	**split;
	char	*key;
	char	*value;

	i = -1;
	while (env[++i])
	{
		split = ft_split(env[i], '=');
		if (split[0])
			key = ft_strdup(split[0]);
		if (split[1])
			value = ft_strdup(split[1]);
		else
			value = ft_strdup("");
		ft_add_element(&env_hastable, key, value);
		free(key);
		free(value);
		ft_free_array(split);
	}
}

t_hashtable	*ft_create_new_env(void)
{
	t_hashtable	*hashtable;
	char		*wd;

	hashtable = ft_create_hashtable(250);
	if (!hashtable)
		return (perror(""), NULL);
	wd = getcwd(NULL, 255);
	ft_add_element(&hashtable, "PWD", wd);
	free(wd);
	ft_add_element(&hashtable, "SHLVL", "1");
	ft_add_element(&hashtable, "_", "env");
	return (hashtable);
}

t_hashtable	*ft_create_hidden(void)
{
	t_hashtable	*hashtable;

	hashtable = ft_create_hashtable(10);
	if (!hashtable)
		return (perror(""), NULL);
	ft_add_element(&hashtable, "PATH",
		"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	ft_add_element(&hashtable, "?", "0");
	return (hashtable);
}

char	*htab_element_to_str(t_element *element)
{
	char	*tmp;
	char	*str;

	str = ft_strjoin("", element->key);
	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strjoin(str, "=");
	free(tmp);
	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strjoin(str, element->value);
	free(tmp);
	if (!str)
		return (NULL);
	return (str);
}
