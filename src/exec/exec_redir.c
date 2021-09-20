/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:22:42 by laube             #+#    #+#             */
/*   Updated: 2021/09/20 01:13:05 by mleblanc         ###   ########.fr       */
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

static void	redir_heredoc(t_redir *redir)
{
	char	*limiter;
	char	*line;
	int		heredoc_fd[2];

	pipe(heredoc_fd);
	limiter = redir->file;
	ft_putstr_fd("> ", STDOUT_FILENO);
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			dup2(heredoc_fd[0], STDIN_FILENO);
			close(heredoc_fd[1]);
			close(heredoc_fd[0]);
			get_next_line(STDIN_FILENO, NULL);
			break ;
		}
		ft_putstr_fd("> ", STDOUT_FILENO);
		ft_putstr_fd(line, heredoc_fd[1]);
		ft_putstr_fd("\n", heredoc_fd[1]);
		free(line);
	}
	get_next_line(STDIN_FILENO, NULL);
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
