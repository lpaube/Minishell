/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:22:42 by laube             #+#    #+#             */
/*   Updated: 2021/10/08 19:43:23 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

static bool	redir_output(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (open_fd == -1)
	{
		pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR);
		return (false);
	}
	dup2(open_fd, STDOUT_FILENO);
	close(open_fd);
	return (true);
}

static bool	redir_append(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (open_fd == -1)
	{
		pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR);
		return (false);
	}
	dup2(open_fd, STDOUT_FILENO);
	close(open_fd);
	return (true);
}

static bool	redir_input(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file, O_RDONLY);
	if (open_fd == -1)
	{
		pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR);
		return (false);
	}
	dup2(open_fd, STDIN_FILENO);
	close(open_fd);
	return (true);
}

static bool	redirect(void *redir_ptr, size_t *n)
{
	t_redir	*redir;

	redir = redir_ptr;
	if (redir->type == OUTPUT)
		return (redir_output(redir));
	else if (redir->type == APPEND)
		return (redir_append(redir));
	else if (redir->type == INPUT)
		return (redir_input(redir));
	else if (redir->type == HEREDOC)
		return (redir_heredoc(redir, (*n)-- == 1));
	return (false);
}

bool	heredoc_count(void *redir)
{
	t_redir	*r;

	r = redir;
	return (r->type == HEREDOC);
}

bool	exec_redirections(t_list *redirs)
{
	size_t	n_heredoc;

	n_heredoc = ft_lstcount_if(redirs, heredoc_count);
	while (redirs)
	{
		if (!redirect(redirs->content, &n_heredoc))
			return (false);
		ft_lstnext(&redirs);
	}
	return (true);
}
