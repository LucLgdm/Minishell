/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:41:04 by andrean           #+#    #+#             */
/*   Updated: 2025/04/07 13:57:26 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "parsing.h"

int			ft_cd(t_ast *node);
int			ft_echo(t_ast *node);
void		ft_exit(t_ast *node, char **paths);
int			ft_export(t_ast *node);
void		get_key_value(char **key, char **value, char *equalsign, char *str);
int			ft_pwd(t_ast *node);
int			ft_unset(t_ast *node);
int			ft_env(t_ast *node);
int			ft_minishellception(t_ast *node, char **paths);

long long	exit_long(t_ast *node, long long *exit_value);

// builtins_utils.c
int			file_exists(char *path_name);
int			get_arg_nb(t_ast *node);
int			ft_no_yes_here(t_ast *node);

#endif