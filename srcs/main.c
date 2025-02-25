/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:07:39 by andrean           #+#    #+#             */
/*   Updated: 2025/02/25 15:00:56 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printlst(t_lst *words)
{
	if (!words)
		printf("Pas de liste\n");
	if (!words->word)
		printf("pas de mot\n");
	if (words->word_type > 4)
		printf("address: %p\nword: %s-------> token : %d\nprev: %p -------> next: %p\n", words->prev, (*(words->prev))->word, (*(words->prev))->word_type, (*(words->prev))->prev, (*(words->prev))->next);
	while (words)
	{
		if ((words)->word_type >= 0)
			printf("address: %p\nword: %s-------> token : %d\nprev: %p -------> next: %p\n", words, words->word, words->word_type, *(words->prev), *(words->next));
		if ((words)->word_type < 0)
		{
			printf("entering sub\n");
			printlst(*((words)->sub));
		}
		words = *(words->next);
	}
}

int	main(void)
{
	char	*line;
	t_lst	*words;

	while (1)
	{
		line = prompt();
		if (line)
		{
			words = separate_line(line);
			if (words)
			{
				get_dollar_in_struct(&words);
				if (words)
				{
					printlst(words);
					ft_lstclearwords(&words);
				}
			}
			free(line);
		}
	}
	return (0);
}
