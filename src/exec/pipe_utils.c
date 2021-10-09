/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 23:03:30 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/08 23:04:10 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
