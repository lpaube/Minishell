/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:29:29 by laube             #+#    #+#             */
/*   Updated: 2021/10/06 15:54:48 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	fd_reset(void)
{
	dup2(g_mini.stdout_fd, STDOUT_FILENO);
	dup2(g_mini.stdin_fd, STDIN_FILENO);
}

void	process_cmd(t_node *cmds)
{
	bool	error;

	while (cmds)
	{
		error = !op_control(cmds);
		if (!error)
		{
			execute(cmds);
			if (!cmds->next)
			{
				fd_reset();
				return ;
			}
		}
		fd_reset();
		if (error)
			return ;
		cmds = cmds->next;
	}
}
