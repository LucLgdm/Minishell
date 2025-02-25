/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:21:57 by andrean           #+#    #+#             */
/*   Updated: 2025/02/25 15:29:44 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_and_or(char *line)
{
	if (!ft_strncmp(line, "&&", 2))
		return (1);
	if (!ft_strncmp(line, "||", 2))
		return (1);
	return (0);
}

int	istoken(char *line)
{
	char	c;

	c = line[0];
	if (c == '\n')
		return (1);
	if (is_and_or(line))
		return (1);
	if (c == '<' || c == '>' || c == '|')
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

char	*subline(char *line, int *i, int *j)
{
	char	*sub;
	int		count;

	sub = NULL;
	count = -1;
	if (*i == *j)
	{
		if (istoken(line + *i))
		{
			sub = get_token(line, i, j);
			return (sub);
		}
	}
	else
	{
		sub = ft_substr(line, *i, *j - *i);
	}
	return (sub);
}

void	ft_skipspaces(char *line, int *i, int *j)
{
	if (ft_isspace(line[*i]))
	{
	while (ft_isspace(line[*i]))
		(*i)++;
	*j = *i;
	}
}

char	*ft_strjoinfree(char *dest, char *src)
{
	int		lendest;
	int		lensrc;
	char	*join;

	if (!src)
		src = ft_calloc(sizeof(char), 1);
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

void	skipquote(char *line, int *i, char c)
{
	int	start;

	start = *i;
	(*i)++;
	while (line[*i] != c && line[*i] != '\0')
		(*i)++;
	if (!line[*i])
		(*i) = start;
	(*i)++;
}
