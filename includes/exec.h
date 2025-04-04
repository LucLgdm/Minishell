/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:50:23 by andrean           #+#    #+#             */
/*   Updated: 2025/04/04 11:48:52 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "./minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

char	**path_tab(t_hashtable *hashtable);
int		redirect_output(char *file, int fd, int append);
int		redirect_input(char *file, int *fd);
int		ft_here_doc(char *limit, int *fdin);
char	**ft_create_envp(void);
int		ft_redirect(t_ast *node);
int		ft_check_for_stop(pid_t *pid, int pid_nb);
pid_t	create_process(t_ast *node, char **paths);
int		ft_do_the_pipe(t_ast *node, char **paths);
void	ft_command_not_found(char **cmd, char **paths);

void	new_handle_dollar(char ***cmd, t_hashtable *env);

int		foundlast(char *name, char *trunc);
char	**onewildtab(void);
char	*ft_strchr_outofquotes(char *str, char c);
void	quotes(char *str, int *i, char **word, char quote_type);

int		*is_in_process(void);

#endif