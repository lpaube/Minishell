/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 01:31:53 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/21 00:16:02 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>

void	stop_heredoc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	g_mini.code = INTERRUPT_SIG;
	exit(INTERRUPT_SIG);
}

void	exec_heredoc(char **line, char *limiter, int *heredoc_fd)
{
	signal(SIGINT, stop_heredoc);
	*line = readline("> ");
	while (*line)
	{
		if (ft_strncmp(*line, limiter, ft_strlen(limiter)) == 0)
		{
			close(heredoc_fd[1]);
			close(heredoc_fd[0]);
			break ;
		}
		ft_putstr_fd(*line, heredoc_fd[1]);
		ft_putstr_fd("\n", heredoc_fd[1]);
		free(*line);
		*line = readline("> ");
	}
	free(*line);
	exit(SUCCESS);
}

void	redir_heredoc(t_redir *redir)
{
	char	*limiter;
	char	*line;
	int		heredoc_fd[2];
	pid_t	pid;

	limiter = redir->file;
	signal(SIGINT, SIG_IGN);
	pipe(heredoc_fd);
	pid = fork();
	if (pid == -1)
		pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR);
	if (pid == 0)
		exec_heredoc(&line, limiter, heredoc_fd);
	waitpid(pid, NULL, 0);
	signal(SIGINT, newline);
	dup2(heredoc_fd[0], STDIN_FILENO);
	close(heredoc_fd[1]);
	close(heredoc_fd[0]);
}
