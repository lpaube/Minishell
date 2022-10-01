#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

void	newline(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_mini.code = INTERRUPT_SIG;
}

void	child_proc_interrupt(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_mini.code = INTERRUPT_SIG;
}

void	child_proc_quit(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit\n", STDOUT_FILENO);
	g_mini.code = QUIT_SIG;
}
