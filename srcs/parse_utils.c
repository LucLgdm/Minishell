/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:21:57 by andrean           #+#    #+#             */
/*   Updated: 2025/02/18 14:19:51 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
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

char	*get_token(char *line, int *i, int *j)
{
	char	c;
	char	*ret;

	c = line[*i];
	if (c == '|' || c == '<' || c == '>' || c == '&')
	{
		if (line[*i] == line[*i + 1])
		{
			ret = ft_calloc(3, sizeof(char));
			if (!ret)
				return (NULL);
			ret[0] = line[*i];
			ret[1] = line[*i];
			*i += 2;
			*j += 2;
			return (ret);
		}
	}
	ret = ft_calloc(2, sizeof(char));
	if (!ret)
		return (NULL);
	ret[0] = line[*i];
	(*i)++;
	(*j)++;
	return (ret);
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
		while (++notvar < *j - *i)
		{
			if (line[notvar + *i] == '$')
				break ;
		}
	}
	else
		notvar = *j - *i;
	if (*i == *j)
		if (istoken(line + *i))
			return (get_token(line, i, j));
	sub = ft_calloc(notvar + 1, sizeof(char));
	if (!sub)
		return (NULL);
	while (++count < notvar && line[*i + count])
		sub[count] = line[*i + count];
	if (notvar != *j - *i)
	{
		vardup = ft_substr(line, *i + notvar + 1, *j - (*i + notvar + 1));
		if (!vardup)
			return (NULL);
		sub = ft_strjoinfree(sub, ft_strdup(getenv(vardup)));
		if (!sub)
			return (NULL);
		free(vardup);
	}
	return (sub);
}

void	ft_skipspaces(char *line, int *i, int *j)
{
	while (ft_isspace(line[*i]))
		(*i)++;
	*j = *i;
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