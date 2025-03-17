/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:24:49 by andrean           #+#    #+#             */
/*   Updated: 2025/03/14 14:43:35 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect(t_ast *node)
{
	t_redir	*redir;

	redir = node->redir;
	while (redir)
	{
		if (redir->redir_type == TOKEN_LESSER)
			redirect_input(redir->value, STDIN_FILENO);
		if (redir->redir_type == TOKEN_GREATGREATER)
			redirect_output(redir->value, STDOUT_FILENO, 1);
		if (redir->redir_type == TOKEN_GREATER)
			redirect_output(redir->value, STDOUT_FILENO, 0);
		if (redir->redir_type == TOKEN_LESSLESSER)
			ft_here_doc(redir->value, STDIN_FILENO);
		redir = redir->next;
	}
}

int	ft_check_for_stop(pid_t *pid, int pid_nb)
{
	int		i;
	int		exit_status;
	int		tmp;
	pid_t	endpid;
	
	i = 0;
	while (g_stop == 0)
	{
		endpid = waitpid(-1, &tmp, WNOHANG);
		if (endpid)
		{
			if (endpid == pid[pid_nb])
				exit_status = tmp;
			i++;
			if (i == pid_nb)
				break ;
		}
	}
	if (i != pid_nb)
	{
		i = -1;
		while (++i < pid_nb)
			kill(pid[i], SIGTERM);
		while (1)
		{
			endpid = waitpid(-1, &tmp, 0);
			if (endpid == pid[pid_nb])
				exit_status = tmp;
			if (endpid == 0)
				break ;
		}
	}
	return(exit_status);
}

char	**path_tab(t_hashtable *hashtable)
{
	char	*path;
	char	*tmp;
	char	**tab;
	int		i;

	i = -1;
	path = NULL;
	if (!hashtable)
	{
		if (!ft_get_element((*get_world())->new_env, "PATH"))
			path = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
		else
			path = ft_get_element((*get_world())->new_env, "PATH")->value;
	}
	else
		if (ft_get_element(hashtable, "PATH"))
			path = ft_get_element(hashtable, "PATH")->value;
	if (!path)
		return (NULL);
	tab = ft_split(path, ':');
	if (!tab)
		;//malloc error
	while (tab[++i])
	{
		tmp = ft_strjoin(tab[i], "/");
		free(tab[i]);
		tab[i] = tmp;
	}
	return (tab);
}

char	*htab_element_to_str(t_element *element)
{
	char	*tmp;
	char	*str;

	str = ft_strjoin("", element->key);
	if (!str)
		;//malloc error
	tmp = str;
	str = ft_strjoin(str, "=");
	free(tmp);
	if (!str)
		;//malloc error
	tmp = str;
	str = ft_strjoin(str, element->value);
	free(tmp);
	if (!str)
		;//malloc error
	return (str);
}

char	**ft_create_envp(void)
{
	t_hashtable	*env;
	char		**envp;
	int			i;
	int			j;

	env = (*get_world())->env;
	if (!env)
		env = (*get_world())->new_env;
	i = 0;
	j = 0;
	envp = ft_calloc(sizeof(char *), env->length);
	while ((i) + j < env->length)
	{
		if (env->table[i + j])
		{
			envp[i] = htab_element_to_str(env->table[i + j]);
			i++;
		}
		else
			j++;
	}
	return (envp);
}