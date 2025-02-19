/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:07:39 by andrean           #+#    #+#             */
/*   Updated: 2025/02/19 11:13:12 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printlst(t_lst *words)
{
	while (words)
	{
		printf("word: %s-------token : %d\n", words->word, words->word_type);
		words = words->next;
	}
}

int	main(int ac, char **av)
{
	char	*line;
	t_lst	*words;

	line = readline("Minishell>");
	while (line)
	{
		line = dollarmanagement(line);
		words = parse_line(line);
		if (words)
		{
			printlst(words);
			ft_lstclearwords(&words);
		}
		line = readline("Minishell>");
	}
	return (0);
}
