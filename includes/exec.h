/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:50:23 by andrean           #+#    #+#             */
/*   Updated: 2025/03/17 14:39:15 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

char	**path_tab(t_hashtable *hashtable);
void	redirect_output(char *file, int fd, int append);
void	redirect_input(char *file, int fd);
void	ft_here_doc(char *limit, int fdin);
char	**ft_create_envp(void);
void	ft_redirect(t_ast *node);
int		ft_check_for_stop(pid_t *pid, int pid_nb);

void	new_handle_dollar(t_ast **node, t_hashtable *env);

#endif