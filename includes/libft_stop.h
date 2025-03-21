/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_stop.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:58:38 by andrean           #+#    #+#             */
/*   Updated: 2025/03/21 17:20:44 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STOP_H
# define LIBFT_STOP_H

#include "../libft/libft.h"

void	*ft_calloc_stop(size_t nmemb, size_t size);
char	*ft_strjoin_stop(char const *s1, char const *s2);
char	**ft_catchartab_stop(char **tab1, char **tab2, int pos);
char	*ft_strdup_stop(const char *s);
void	ft_strncat_stop(char **dest, const char *src, size_t n);
char	*ft_substr_stop(char const *s, unsigned int start, size_t len);
char	*ft_itoa_stop(int n);
char	**ft_split_stop(char const *s, char c);

#endif