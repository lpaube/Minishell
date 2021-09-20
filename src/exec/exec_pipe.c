/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:18:50 by laube             #+#    #+#             */
/*   Updated: 2021/09/19 22:10:37 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "tokenizer.h"

static void	left_pipe(t_node *cmds)
{
	if (cmds->prev)
	{
		dup2(cmds->prev->fd[0], 0);
		close(cmds->prev->fd[0]);
	}
}

static void	right_pipe(t_node *cmds)
{
	if (cmds->next)
		dup2(cmds->fd[1], 1);
}

void	op_control(t_node *cmds)
{
	pipe(cmds->fd);
	left_pipe(cmds);
	ft_lstiter(cmds->redirs, do_redirections);
	right_pipe(cmds);
	close(cmds->fd[1]);
	if (!cmds->next)
		close(cmds->fd[0]);
}
