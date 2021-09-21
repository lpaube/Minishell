/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 01:31:53 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/22 05:24:42 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>

static void	stop_heredoc(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit(INTERRUPT_SIG);
}

static size_t	max_value(size_t a, size_t b)
{
	if (a >= b)
		return (a);
	return (b);
}

static void	exec_heredoc(const char *limiter, int *heredoc_fd)
{
	char	*line;
	size_t	count;

	signal(SIGINT, stop_heredoc);
	line = readline("> ");
	while (line)
	{
		count = max_value(ft_strlen(line), ft_strlen(limiter));
		if (ft_strncmp(line, limiter, count) == 0)
		{
			close(heredoc_fd[1]);
			close(heredoc_fd[0]);
			break ;
		}
		ft_putstr_fd(line, heredoc_fd[1]);
		ft_putstr_fd("\n", heredoc_fd[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	exit(SUCCESS);
}

bool	redir_heredoc(t_redir *redir)
{
	char	*limiter;
	int		heredoc_fd[2];
	pid_t	pid;
	int		wstatus;

	limiter = redir->file;
	signal(SIGINT, SIG_IGN);
	pipe(heredoc_fd);
	pid = fork();
	if (pid == -1)
		pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR);
	if (pid == 0)
		exec_heredoc(limiter, heredoc_fd);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, newline);
	if (WIFEXITED(wstatus))
		g_mini.code = WEXITSTATUS(wstatus);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == SUCCESS)
		dup2(heredoc_fd[0], STDIN_FILENO);
	close(heredoc_fd[1]);
	close(heredoc_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == INTERRUPT_SIG)
		return (false);
	return (true);
}
