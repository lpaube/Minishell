/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:29:29 by laube             #+#    #+#             */
/*   Updated: 2021/09/19 00:39:31 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parse.h"
#include "minishell.h"
#include "exec.h"
#include <stdio.h>

static bool	dispatch_cmd(t_node *node)
{
	if (ft_strncmp(node->cmd, "echo", 5) == 0)
		ft_echo(node);
	else if (ft_strncmp(node->cmd, "pwd", 4) == 0)
		ft_pwd(node);
	else if (ft_strncmp(node->cmd, "cd", 3) == 0)
		ft_cd(node);
	else if (ft_strncmp(node->cmd, "env", 4) == 0)
		ft_env(node);
	else if (ft_strncmp(node->cmd, "unset", 6) == 0)
		ft_unset(node);
	else if (ft_strncmp(node->cmd, "export", 7) == 0)
		ft_export(node);
	else if (ft_strncmp(node->cmd, "exit", 5) == 0)
		return (ft_exit(node));
	else
		ft_cmd(node);
	return (false);
}

bool	execute(t_node *node)
{
	if (node->cmd)
		node->cmd = interpolate(node->cmd);
	interpolate_arr(node->args);
	interpolate_redirs(node->redirs);
	if (node->cmd)
		if (dispatch_cmd(node))
			return (true);
	return (false);
}

void	pipe_control(t_node *cmds)
{
	int	open_fd;
	t_redir	*redir;
	// char	*line;

	pipe(cmds->fd);
	if (cmds->prev)
	{
		dup2(cmds->prev->fd[0], 0);
		close(cmds->prev->fd[0]);
	}
	if (cmds->next)
	{
		dup2(cmds->fd[1], 1);
		close(cmds->fd[1]);
	}
	if (cmds->redirs)
		redir = cmds->redirs->content;
	while (cmds->redirs)
	{
		if (redir->type == OUTPUT)
		{
			open_fd = open(redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			dup2(open_fd, 1);
			close(open_fd);
		}
		else if (redir->type == APPEND)
		{
			open_fd = open(redir->file, O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(open_fd, 1);
			close(open_fd);
		}
		else if (redir->type == INPUT)
		{
			open_fd = open(redir->file, O_RDONLY);
			dup2(open_fd, 0);
			close(open_fd);
		}
		else if (redir->type == HEREDOC)
		{
			(void)open_fd;
		}
		cmds->redirs = cmds->redirs->next;
		if (cmds->redirs)
			redir = cmds->redirs->content;
	}
}

bool	process_cmd(t_node *cmds)
{
	pipe(g_mini.fd);
	while (cmds)
	{
		// printf("EXEC:cmds: %s | next-addr: %p\n", cmds->cmd, cmds->next);
		pipe_control(cmds);
		if (execute(cmds) && !cmds->next)
		{
			return (true);
		}
		dup2(g_mini.stdout_fd, 1);
		dup2(g_mini.stdin_fd, 0);
		cmds = cmds->next;
	}
	return (false);
}
