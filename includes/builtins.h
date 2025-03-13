/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:41:04 by andrean           #+#    #+#             */
/*   Updated: 2025/03/13 16:00:00 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int		get_arg_nb(t_ast *node);
int		ft_cd(t_ast *node);
int		ft_echo(t_ast *node);
void	ft_exit(t_ast *node);
int		ft_export(t_ast *node);
int		ft_pwd(t_ast *node);
int		ft_unset(t_ast *node);
int		ft_env(t_ast *node);

#endif