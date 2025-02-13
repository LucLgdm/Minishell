/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:15:53 by andrean           #+#    #+#             */
/*   Updated: 2024/12/12 09:45:58 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_box
{
	char				*tmp;
	char				*line;
	char				*rest;
	long long int		nbread;
}	t_box;

typedef struct s_join
{
	unsigned long int	j;
	unsigned long int	i;
	char				*tmp;
}	t_join;

char			*get_next_line(int fd, int freebuff);
void			boxnuller(t_box *box);
int				linechecker(t_box *box);
unsigned long	ft_strlcpy(char *dst, const char *src, unsigned long siz);
void			ft_bzero(void *s, unsigned long n);
void			freeptr(char **ptr);

#endif
