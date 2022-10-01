#include "builtin.h"
#include "parse.h"
#include "minishell.h"
#include "exec.h"
#include <stdio.h>

static void	dispatch_cmd(t_node *node)
{
	if (ft_strncmp(node->argv[0], "echo", 5) == 0)
		ft_echo(node);
	else if (ft_strncmp(node->argv[0], "pwd", 4) == 0)
		ft_pwd(node);
	else if (ft_strncmp(node->argv[0], "cd", 3) == 0)
		ft_cd(node);
	else if (ft_strncmp(node->argv[0], "env", 4) == 0)
		ft_env(node);
	else if (ft_strncmp(node->argv[0], "unset", 6) == 0)
		ft_unset(node);
	else if (ft_strncmp(node->argv[0], "export", 7) == 0)
		ft_export(node);
	else if (ft_strncmp(node->argv[0], "exit", 5) == 0)
		ft_exit(node);
	else
		ft_cmd(node);
}

static void	execute(t_node *node)
{
	interpolate_arr(node->argv);
	interpolate_redirs(node->redirs);
	if (node->argv[0])
		dispatch_cmd(node);
}

static bool	process_heredocs(t_node *cmds)
{
	while (cmds)
	{
		if (!exec_heredocs(cmds->redirs, cmds->fd[0]))
			return (true);
		cmds = cmds->next;
	}
	return (false);
}

void	process_cmd(t_node *cmds)
{
	t_node	*start;
	bool	error;

	start = cmds;
	init_pipes(start);
	error = process_heredocs(cmds);
	while (!error && cmds)
	{
		error = !op_control(cmds);
		if (!error)
		{
			execute(cmds);
			if (!cmds->next)
				break ;
			fd_reset();
		}
		if (error)
			break ;
		cmds = cmds->next;
	}
	close_pipes(start);
	fd_reset();
}
