/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:17:24 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/07 16:06:06 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_stop;

static void	handle_prompt(t_world **world)
{
	add_history((*world)->prompt);
	if (ft_strcmp((*world)->prompt, "clean") == 0)
	{
		rl_clear_history();
		printf("\033[0;32mHistory cleaned\033[0m\n");
	}
	else
	{
		fill_tree(world);
		exec_tree(*world, (*world)->tree, 1);
		unlink(".heredoc");
	}
}

void	prompt(t_world *world)
{
	int	*is_process;

	is_process = is_in_process();
	while (42)
	{
		*is_process = 1;
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		world->prompt = readline("\001\033[3;33m\002Minishell > \001\033[0m\002 ");
		g_stop = 0;
		signal(SIGINT, handle_signal_afterprompt);
		if (!world->prompt)
		{
			printf("\033[0;32mFrom Minishell with Love !\033[0m\n");
			free_all(&world);
			exit(EXIT_SUCCESS);
		}
		if (ft_strlen(world->prompt) > 0)
			handle_prompt(&world);
		free(world->prompt);
		ft_free_ast(&world->tree);
		ft_free_token(&world->tokenlist, 1);
	}
}

t_hashtable	*ft_create_env_hashtable(char **env, t_hashtable **env_hashtable)
{
	int		len_env;
	char	*shlvl;

	len_env = ft_arraylen(env);
	if (len_env == 0)
		return (NULL);
	len_env = ft_next_prime(3 * len_env);
	*env_hashtable = ft_create_hashtable(len_env);
	if (!*env_hashtable)
		stop_when_calloc_fail();
	ft_env_to_hashtable(env, *env_hashtable);
	if (*env_hashtable)
	{
		shlvl = ft_itoa_stop(ft_atoi(ft_get_element(*env_hashtable,
						"SHLVL")->value) + 1);
		*env_hashtable = ft_modify_value(*env_hashtable, "SHLVL", shlvl, 0);
		free(shlvl);
	}
	return (*env_hashtable);
}

char	**ft_sub_envp(int *i, int *j, t_element *element, char **envp)
{
	char	*str;
	char	**newline;

	while (element)
	{
		if (element->value)
		{
			newline = ft_calloc(sizeof(char *), 2);
			if (!newline)
				return (NULL);
			str = htab_element_to_str(element);
			if (!str)
				return (ft_free_array(newline), NULL);
			newline[0] = str;
			envp = ft_catchartab(envp, newline, ft_arraylen(envp));
			if (!envp)
				return (NULL);
			(*i)++;
			if (element->next)
				(*j)--;
		}
		element = element->next;
	}
	return (envp);
}

char	**ft_create_envp(void)
{
	t_hashtable	*env;
	t_element	*element;
	char		**envp;
	int			i;
	int			j;

	env = (*get_world())->env;
	if (!env)
		env = (*get_world())->new_env;
	i = 0;
	j = 0;
	envp = ft_calloc(sizeof(char *), 1);
	if (!envp)
		return (NULL);
	while (i + j < env->length)
	{
		element = env->table[i + j];
		envp = ft_sub_envp(&i, &j, element, envp);
		if (!envp)
			return (NULL);
		if (!env->table[i + j] || !env->table[i + j]->value)
			j++;
	}
	return (envp);
}
