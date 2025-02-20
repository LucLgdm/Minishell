
#include "../../includes/minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

char	*prompt(void)
{
	char	*input;

	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	input = readline("\033[33mMinishell > \033[0m");
	if (!input)
		exit(0);
	if (*input)
		add_history(input);
	if (strcmp(input, "clean") == 0)
	{
		rl_clear_history();
		printf("\033[0;32mHistorique effacé\033[0m\n");
		free(input);
		return (NULL);
	}
	return (input);
}
