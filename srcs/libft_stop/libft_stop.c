/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:49:25 by andrean           #+#    #+#             */
/*   Updated: 2025/03/21 17:07:35 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_stop(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	if (len == 0)
		return (ft_strdup_stop(""));
	str = (char *)ft_calloc_stop((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		str[i] = s[start + i];
	return (str);
}

void	ft_strncat_stop(char **dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	src_len;
	char	*new_str;

	if (!src || n == 0)
		return ;
	if (*dest)
		dest_len = ft_strlen(*dest);
	else
		dest_len = 0;
	src_len = ft_strnlen(src, n);
	new_str = ft_calloc_stop(dest_len + src_len + 1, 1);
	if (!new_str)
		return ;
	if (*dest)
		ft_strcpy(new_str, *dest);
	ft_strlcat(new_str, src, dest_len + src_len + 1);
	free(*dest);
	*dest = new_str;
}

char	*ft_strdup_stop(const char *s)
{
	char	*cpy;
	size_t	size_s;
	size_t	i;

	i = 0;
	size_s = ft_strlen(s);
	cpy = (char *)ft_calloc_stop((size_s + 1), sizeof(char));
	if (!cpy)
		return (NULL);
	while (i < size_s)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_catchartab_stop(char **tab1, char **tab2, int pos)
{
	int		n;
	int		m;
	char	**output;
	int		i;

	n = ft_arraylen(tab1);
	m = ft_arraylen(tab2);
	output = ft_calloc_stop((n + m + 1), sizeof(char *));
	if (!output)
		return (NULL);
	i = -1;
	while (++i < pos)
		output[i] = ft_strdup_stop(tab1[i]);
	i = -1;
	while (++i < m)
		output[pos + i] = ft_strdup_stop(tab2[i]);
	i = pos + 1;
	while (i < n)
	{
		output[i + m - 1] = ft_strdup_stop(tab1[i]);
		i++;
	}
	ft_free_array(tab1);
	ft_free_array(tab2);
	return (output);
}

char	*ft_strjoin_stop(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_size;
	size_t	s2_size;
	size_t	i;

	i = -1;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	str = (char *)ft_calloc_stop((s1_size + s2_size + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (++i < s1_size)
		str[i] = s1[i];
	i = -1;
	while (++i < s2_size)
		str[s1_size + i] = s2[i];
	str[s1_size + i] = '\0';
	return (str);
}
