/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:10:42 by andrean           #+#    #+#             */
/*   Updated: 2024/12/13 14:57:04 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//detects listed specials
int	isspecial(const char *s)
{
	char	*set;
	int		i;

	set = "cspdiuxX%";
	i = 0;
	if (s[0] == '%')
	{
		while (set[i])
		{
			if (set[i] == s[1])
				return (1);
			i++;
		}
	}
	return (0);
}

//puts everything in a list, including specials.

void	lststocker(const char *s, t_list **lst)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (s[i])
	{
		if (isspecial(s + i))
		{
			ft_lstadd_back(lst, ft_lstnew(ft_substr(s, i, 2)));
			i += 2;
			start = i;
		}
		else
		{
			while (s[i] && (!isspecial(s + i)))
				i++;
			ft_lstadd_back(lst, ft_lstnew(ft_substr(s, start, i - start)));
		}
	}
}

void	printspecial(char c, va_list ap, int *ret)
{
	if (c == 'c')
		ft_putchar_ret((char)va_arg(ap, int), ret);
	if (c == 's')
		ft_putstrl(va_arg(ap, char *), ret);
	if (c == 'p')
		ft_printaddress(va_arg(ap, void *), ret);
	if (c == 'i' || c == 'd')
		ft_putnbrl(va_arg(ap, int), ret);
	if (c == 'u')
		ft_printnum(va_arg(ap, unsigned int), ret);
	if (c == 'x' || c == 'X')
		ft_printhex(va_arg(ap, long unsigned int), (c - 88) / 32, ret);
	if (c == '%')
		ft_putchar_ret('%', ret);
}

void	ft_printlist(t_list *lst, va_list ap, int *ret)
{
	while (lst)
	{
		if (isspecial((const char *)(lst->content)))
		{
			printspecial((*(char *)((lst->content) + 1)), ap, ret);
			lst = lst->next;
		}
		else
		{
			ft_putstrl((char *)(lst->content), ret);
			lst = lst->next;
		}
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	t_list	**lst;
	t_list	**start;
	int		ret;

	ret = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	lst = calloc(1, sizeof(t_list *));
	lststocker(format, lst);
	start = lst;
	ft_printlist(*lst, ap, &ret);
	va_end(ap);
	ft_lstclear(start, free);
	return (ret);
}
