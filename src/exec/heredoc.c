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

static void	exec_heredoc(const char *limiter, int *heredoc_fd)
{
	char	*line;

	signal(SIGINT, stop_heredoc);
	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, limiter) == 0)
		{
			close(heredoc_fd[1]);
			close(heredoc_fd[0]);
			break ;
		}
		ft_putendl_fd(line, heredoc_fd[1]);
		free(line);
		line = readline("> ");
	}
	free(line);
	exit(SUCCESS);
}

static bool	redir_heredoc(t_redir *redir, int fd, bool last)
{
	int		heredoc_fd[2];
	pid_t	pid;
	int		wstatus;

	signal(SIGINT, SIG_IGN);
	pipe(heredoc_fd);
	pid = fork();
	if (pid == -1)
		pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR);
	if (pid == 0)
		exec_heredoc(redir->file, heredoc_fd);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, newline);
	if (WIFEXITED(wstatus))
		g_mini.code = WEXITSTATUS(wstatus);
	if (last)
		dup2(heredoc_fd[0], fd);
	close(heredoc_fd[1]);
	close(heredoc_fd[0]);
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == INTERRUPT_SIG)
		return (false);
	return (true);
}

static bool	heredoc_count(void *redir)
{
	t_redir	*r;

	r = redir;
	return (r->type == HEREDOC);
}

bool	exec_heredocs(t_list *redirs, int stdin_fd)
{
	t_redir	*redir;
	size_t	count;

	count = ft_lstcount_if(redirs, heredoc_count);
	while (redirs)
	{
		redir = redirs->content;
		if (redir->type == HEREDOC)
		{
			if (!redir_heredoc(redir, stdin_fd, count-- == 1))
				return (false);
		}
		ft_lstnext(&redirs);
	}
	return (true);
}
