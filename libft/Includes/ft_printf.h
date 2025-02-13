/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:14:42 by andrean           #+#    #+#             */
/*   Updated: 2024/11/18 09:42:19 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int		ft_printf(const char *format, ...);
void	ft_printnum(unsigned int nbr, int *ret);
void	ft_printaddress(void *adress, int *ret);
void	ft_printhex(long unsigned int nbr, int islower, int *ret);
void	ft_nbrprinter(long unsigned int nbr, char *base, int len, int *ret);
int		isspecial(const char *s);
void	lststocker(const char *s, t_list **lst);
void	printspecial(char c, va_list ap, int *ret);
void	ft_printlist(t_list *lst, va_list ap, int *ret);
void	ft_putchar_ret(char c, int *ret);
void	ft_putstrl(char *s, int *ret);
void	ft_putnbrl(int n, int *ret);

#endif
