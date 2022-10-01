#include "minishell.h"

void	fd_reset(void)
{
	dup2(g_mini.stdout_fd, STDOUT_FILENO);
	dup2(g_mini.stdin_fd, STDIN_FILENO);
}

void	init_pipes(t_node *cmds)
{
	while (cmds)
	{
		pipe(cmds->fd);
		cmds = cmds->next;
	}
}

void	close_pipes(t_node *cmds)
{
	while (cmds)
	{
		close(cmds->fd[0]);
		close(cmds->fd[1]);
		cmds = cmds->next;
	}
}
