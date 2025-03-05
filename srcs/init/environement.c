/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:17:24 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/05 11:11:24 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prompt(t_world *world)
{
	while (42)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		world->prompt = readline("\001\033[3;33m\002Minishell > \001\033[0m\002 ");
		if (!world->prompt || (strcmp(world->prompt, "exit") == 0))
		{
			printf("\033[0;32mFrom Minishell with Love !\033[0m\n");
			break ;
		}
		if (ft_strlen(world->prompt) > 0)
		{
			add_history(world->prompt);
			if (strcmp(world->prompt, "clean") == 0)
			{
				rl_clear_history();
				printf("\033[0;32mHistory cleaned\033[0m\n");
			}
			else
				fill_tree(world);
		}
		free(world->prompt);
	}
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

t_world	*get_world(void)
{
	static t_world	world;

	return (&world);
}

t_hashtable	*ft_create_env_hashtable(char **env)
{
	t_hashtable	*env_hashtable;
	int			len_env;

	len_env = ft_arraylen(env);
	if (len_env == 0)
	{
		env_hashtable = ft_create_hashtable(250);
		return (env_hashtable);
	}
	len_env = ft_next_prime(3 * len_env);
	env_hashtable = ft_create_hashtable(len_env);
	if (!env_hashtable)
		return (NULL);
	ft_env_to_hashtable(env, env_hashtable);
	return (env_hashtable);
}

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
		ft_add_element(env_hastable, key, value);
		free(key);
		free(value);
		ft_free_array(split);
	}
}
