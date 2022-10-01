#include "exec.h"
#include "tokenizer.h"
#include "minishell.h"
#include <sys/stat.h>
#include <string.h>

static void	left_pipe(t_node *cmds)
{
	if (cmds->prev)
	{
		dup2(cmds->prev->fd[0], STDIN_FILENO);
		close(cmds->prev->fd[0]);
	}
}

static void	right_pipe(t_node *cmds)
{
	if (cmds->next)
		dup2(cmds->fd[1], STDOUT_FILENO);
}

static bool	input_file_exist(void *redir_ptr)
{
	struct stat	buf;
	t_redir		*redir;

	redir = redir_ptr;
	if (redir->type != INPUT)
		return (true);
	if (stat(redir->file, &buf) == -1)
	{
		pset_err(SHELL_NAME, redir->file, strerror(errno), GENERIC_ERR);
		return (false);
	}
	return (true);
}

static bool	is_stdout_redir(void *redir_ptr)
{
	t_redir		*redir;

	redir = redir_ptr;
	if (redir->type == OUTPUT || redir->type == APPEND)
		return (true);
	return (false);
}

bool	op_control(t_node *cmds)
{
	left_pipe(cmds);
	if (!ft_lstall(cmds->redirs, input_file_exist))
		return (false);
	if (!exec_redirections(cmds->redirs, cmds->fd))
		return (false);
	if (!ft_lstany(cmds->redirs, is_stdout_redir))
		right_pipe(cmds);
	close(cmds->fd[1]);
	return (true);
}
