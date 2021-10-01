/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:16:38 by laube             #+#    #+#             */
/*   Updated: 2021/10/01 19:12:23 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

static char	*find_executable(char **dirs, const char *cmd)
{
	struct stat	buf;
	t_string	*str;
	size_t		i;

	i = 0;
	while (dirs[i])
	{
		str = ft_str_new_copy(dirs[i]);
		ft_str_add_back(str, '/');
		ft_str_append_cstr(str, cmd);
		if (stat(ft_str_data(str), &buf) == 0 && !S_ISDIR(buf.st_mode))
			return (ft_str_take(str));
		ft_str_free(str);
		++i;
	}
	return (NULL);
}

static bool	is_in_cwd(const char *cmd)
{
	struct stat	buf;

	if ((*cmd == '.' || *cmd == '/') && stat(cmd, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
		{
			errno = EISDIR;
			pset_err(SHELL_NAME, cmd, strerror(errno), NOT_EXEC_ERR);
			return (false);
		}
		return (true);
	}
	return (false);
}

static char	*get_cmd_path(const char *cmd)
{
	char	*path;
	char	*absolute;
	char	**dirs;

	if (is_in_cwd(cmd))
		return (ft_strdup(cmd));
	if (errno == EISDIR)
		return (NULL);
	path = ft_getenv("PATH");
	if (!path)
	{
		pset_err(SHELL_NAME, cmd, CMD_NOT_FOUND, ENVIRONMENT_ERR);
		return (NULL);
	}
	dirs = ft_split(path, ':');
	absolute = find_executable(dirs, cmd);
	if (!absolute)
		pset_err(SHELL_NAME, cmd, CMD_NOT_FOUND, ENVIRONMENT_ERR);
	ft_strarr_free(dirs);
	return (absolute);
}

static void	exec_binary(const char *path, char *const *argv)
{
	execve(path, argv, g_mini.env);
	pset_err(SHELL_NAME, path, strerror(errno), NOT_EXEC_ERR);
	exit(NOT_EXEC_ERR);
}

void	ft_cmd(t_node *node)
{
	char	*path;
	pid_t	pid;
	int		wstatus;

	path = get_cmd_path(node->argv[0]);
	if (!path)
		return ;
	pid = fork();
	if (pid == -1)
	{
		free(path);
		return (pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR));
	}
	signal(SIGINT, child_proc_interrupt);
	signal(SIGQUIT, child_proc_quit);
	if (pid == 0)
		exec_binary(path, node->argv);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, newline);
	signal(SIGQUIT, SIG_IGN);
	if (WIFEXITED(wstatus))
		g_mini.code = WEXITSTATUS(wstatus);
	free(path);
}
