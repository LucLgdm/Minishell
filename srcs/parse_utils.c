/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:21:57 by andrean           #+#    #+#             */
/*   Updated: 2025/02/13 15:07:35 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	isend(char c)
{
	if (c == '\0' || c == '\n')
		return (1);
	return (0);
}

int	isoperator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '>>' || c == '<<')
		return (1);
	return (0);
}

char	*ft_strjoinfree(char *dest, char *src)
{
	int		lendest;
	int		lensrc;
	char	*join;

	if (!dest)
		return (src);
	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	join = (char *)ft_calloc((lensrc + lendest + 1), sizeof(char));
	if (!join)
	{
		free(src);
		free(dest);
		return (NULL);
	}
	ft_strlcat(join, dest, lendest + lensrc + 1);
	ft_strlcat(join, src, lendest + lensrc + 1);
	free(src);
	free(dest);
	return (join);
}