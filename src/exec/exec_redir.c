/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 18:22:42 by laube             #+#    #+#             */
/*   Updated: 2021/09/19 18:36:21 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	redir_output(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(open_fd, 1);
	close(open_fd);
}

void	redir_append(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	dup2(open_fd, 1);
	close(open_fd);
}

void	redir_input(t_redir *redir)
{
	int	open_fd;

	open_fd = open(redir->file, O_RDONLY);
	dup2(open_fd, 0);
	close(open_fd);
}

void	redir_heredoc(t_redir *redir)
{
	char	*limiter;
	char	*line;
	int		heredoc_fd[2];

	pipe(heredoc_fd);
	limiter = redir->file;
	ft_putstr_fd("> ", 1);
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			dup2(heredoc_fd[0], 0);
			close(heredoc_fd[1]);
			close(heredoc_fd[0]);
			break ;
		}
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, heredoc_fd[1]);
		ft_putstr_fd("\n", heredoc_fd[1]);
		free(line);
	}
}
