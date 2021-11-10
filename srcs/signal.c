#include "../includes/minishell.h"

void	catch_signal(int signal, siginfo_t *info, void *context)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// kill(info->si_pid, SIGKILL);
	}
	(void)signal;
	(void)context;
	(void)info;
}
