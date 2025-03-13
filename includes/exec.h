/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:50:23 by andrean           #+#    #+#             */
/*   Updated: 2025/03/13 18:01:12 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "./minishell.h"

char	**path_tab(t_hashtable *hashtable);
void	redirect_output(char *file, int fd, int append);
void	redirect_input(char *file, int fd);
void	ft_here_doc(char *limit, int fdin);
char	**ft_create_envp(void);
void	ft_redirect(t_ast *node);
int	ft_check_for_stop(pid_t *pid, int pid_nb);

#endif