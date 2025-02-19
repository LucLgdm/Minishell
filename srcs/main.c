/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:07:39 by andrean           #+#    #+#             */
/*   Updated: 2025/02/19 13:58:03 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printlst(t_lst *words)
{
	if (!words)
		printf("Pas de liste\n");
	if (!words->word)
		printf("pas de mot\n");
	while (words)
	{
		printf("word: %s-------> token : %d\n", words->word, words->word_type);
		words = words->next;
	}
}

int	main(void)
{
	char	*line;
	t_lst	*words;

	line = readline("Minishell > ");
	while (line)
	{
		line = dollarmanagement(line);
		words = parse_line(line);
		if (words)
		{
			printlst(words);
			ft_lstclearwords(&words);
		}
		free(line);
		line = readline("Minishell > ");
	}
	return (0);
}
