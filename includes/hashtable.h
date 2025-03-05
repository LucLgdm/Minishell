/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:24:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/05 10:55:40 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include <stdlib.h>
# include <stddef.h>
# include "../libft/libft.h"

typedef struct s_element
{
	char				*key;
	char				*value;
	struct s_element	*next;
}	t_element;

typedef struct s_hashtable
{
	t_element	**table;
	int			length;
}	t_hashtable;

// create.c
t_hashtable	*ft_create_hashtable(int length);
t_element	*ft_create_element(char *key, char *value);
int			ft_hash(char *key, int length);

// operation.c
t_hashtable	*ft_add_element(t_hashtable *ht, char *key, char *value);
t_element	*ft_get_element(t_hashtable *htable, char *key);
t_hashtable	*ft_delete_element(t_hashtable *ht, char *key);
void		ft_print_hashtable(t_hashtable *hashtable, char *delimeter);


#endif