/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:21:57 by andrean           #+#    #+#             */
/*   Updated: 2025/02/17 17:50:26 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	istoken(char *line)
{
	char	c;

	c = line[0];
	if (c == '\n')
		return (1);
	if (!ft_strncmp(line, "&&", 2))
		return (1);
	if (!ft_strncmp(line, ">>", 2))
		return (1);
	if (!ft_strncmp(line, "<<", 2))
		return (1);
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

char	*subline(char *line, int *i, int *j, int manage_dollar)
{
	char	*sub;
	int		count;
	int		notvar;
	char	*vardup;

	notvar = -1;
	count = -1;
	if (manage_dollar)
	{
		while (++notvar && notvar < *j - *i)
			if (line[notvar + *i] == '$')
				break ;
	}
	else
		notvar = *j - *i;
	if (*i = *j)
		if (istoken(line + i))
			//
	else
		sub = ft_calloc(notvar + 1, sizeof(char));
	if (!sub)
		return (NULL);
	while (++count < notvar && line[i + count])
		sub[count] = line[i + count];
	if (notvar != j - i)
	{
		vardup = ft_substr(line, i + vardup + 1, j - (i + vardup + 1))
		sub = ft_strjoinfree(sub, ft_strdup(getenv(vardup)));
	}
	return (sub);
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