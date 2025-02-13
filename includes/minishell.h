/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:00:42 by andrean           #+#    #+#             */
/*   Updated: 2025/02/13 15:59:47 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"


//structure temporaire a passer pour executer chaque commande
typedef struct s_cmd
{
	char			**args;
	char			**paths;
}	t_cmd;


//liste chainee pour les differents mots
typedef struct s_lst
{
	char			*word;
	int				word_type;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_lst;

//utils
int		isspace(char c);
void	ft_lstback(t_lst **lst, t_lst *new);
t_lst	*ft_lstnewword(char *word);
void	ft_lstdelone(t_lst *lst);
void	ft_lstclearwords(t_lst **lst);
char	*ft_strjoinfree(char *dest, char *src);

#endif