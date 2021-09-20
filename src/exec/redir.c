/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:22:42 by laube             #+#    #+#             */
/*   Updated: 2021/09/20 01:32:23 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <fcntl.h>
#include <stdlib.h>

static void	redir_output(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(open_fd, STDOUT_FILENO);
	close(open_fd);
}

static void	redir_append(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(open_fd, STDOUT_FILENO);
	close(open_fd);
}

static void	redir_input(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file, O_RDONLY);
	dup2(open_fd, STDIN_FILENO);
	close(open_fd);
}

void	do_redirection(void *redir_ptr)
{
	t_redir	*redir;

	redir = redir_ptr;
	if (redir->type == OUTPUT)
		redir_output(redir);
	else if (redir->type == APPEND)
		redir_append(redir);
	else if (redir->type == INPUT)
		redir_input(redir);
	else if (redir->type == HEREDOC)
		redir_heredoc(redir);
}
