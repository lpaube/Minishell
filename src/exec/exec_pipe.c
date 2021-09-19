/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:18:50 by laube             #+#    #+#             */
/*   Updated: 2021/09/19 18:23:49 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	redir_control(t_node *cmds)
{
	t_redir	*redir;
	
	while (cmds->redirs)
	{
		redir = cmds->redirs->content;
		if (redir->type == OUTPUT)
			redir_output(redir);
		else if (redir->type == APPEND)
			redir_append(redir);
		else if (redir->type == INPUT)
			redir_input(redir);
		else if (redir->type == HEREDOC)
			redir_heredoc(redir);
		cmds->redirs = cmds->redirs->next;
	}
}

void	left_pipe(t_node *cmds)
{
	if (cmds->prev)
	{
		dup2(cmds->prev->fd[0], 0);
		close(cmds->prev->fd[0]);
	}
}

void	right_pipe(t_node *cmds)
{
	if (cmds->next)
		dup2(cmds->fd[1], 1);
}

void	op_control(t_node *cmds)
{
	pipe(cmds->fd);
	left_pipe(cmds);
	redir_control(cmds);
	right_pipe(cmds);

	close(cmds->fd[1]);
	if (!cmds->next)
		close(cmds->fd[0]);
}