/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:15:58 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/21 17:30:28 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

//liste chainee pour les differents mots
typedef struct s_lst
{
	char			*word;
	int				word_type;
	struct s_lst	**next;
	struct s_lst	**prev;
	struct s_lst	**sub;
}	t_lst;

typedef struct s_world
{
	char	*home;
	char	*prompt;
	t_list	*env;
	t_lst	*prompt_read;
}	t_world;




// output
void	handle_signal(int sig);

// environement
void	copy_env(t_list **env, char **envp, t_world *world);
void	prompt(t_world *world);
void	parse_prompt(t_world *world);

// free
void	free_all(t_world *world);

t_lst	*parse_line(char *line);

#endif