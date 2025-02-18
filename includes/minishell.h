/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:00:42 by andrean           #+#    #+#             */
/*   Updated: 2025/02/18 13:29:03 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define INPUT		1 // '<'
# define TRUNC		2 // '>'
# define HEREDOC	3 // '<<'
# define APPEND		4 // '>>'
# define PIPE		5 // '|'
# define OR			6 // '||'
# define AND		7 // '&&'
# define CMD		8
# define ARG		9

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

//parsing
t_lst	*parse_line(char *line);
//utils parsing
void	ft_skipspaces(char *line, int *i, int *j);
char	*subline(char *line, int *i, int *j, int manage_dollar);
int		istoken(char *line);
int		ft_isspace(char c);
void	ft_lstback(t_lst **lst, t_lst *new);
t_lst	*ft_lstnewword(char *word, int ignoretoken);
void	ft_lstclearwords(t_lst **lst);
char	*ft_strjoinfree(char *dest, char *src);

#endif