/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:24:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/21 17:20:59 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include "libft_stop.h"

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

// hashtable_creation.c
t_hashtable	*ft_create_hashtable(int length);
t_element	*ft_create_element(char *key, char *value);
int			ft_hash(char *key, int length);

// operation.c
t_hashtable	*ft_add_element(t_hashtable **ht, char *key, char *value);
t_element	*ft_get_element(t_hashtable *htable, char *key);
void		ft_print_hashtable(t_hashtable *hashtable, char *delimeter);
/*si add > 0, la fonction concatene la valeur existente avec la nouvelle */
/*sinon elle remplace */
t_hashtable	*ft_modify_value(t_hashtable *ht, char *key, char *value, int add);
t_hashtable	*ft_remove_element(t_hashtable *htable, char *key);

// hashtable_env.c
t_hashtable	*ft_create_env_hashtable(char **env);
t_hashtable	*ft_create_hidden(void);
t_hashtable	*ft_create_new_env(void);
void		ft_env_to_hashtable(char **env, t_hashtable *env_hastable);
char		*htab_element_to_str(t_element *element);

void		ft_free_element(t_element **element);

// free_hashtable
void		ft_free_hasht(t_hashtable *hasht);

#endif