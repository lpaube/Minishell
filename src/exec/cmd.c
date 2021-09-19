/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:16:38 by laube             #+#    #+#             */
/*   Updated: 2021/09/19 00:24:08 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

static char	*find_cmd(char **dirs, const char *cmd)
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
		if (stat(ft_str_data(str), &buf) == 0)
			return (ft_str_take(str));
		ft_str_free(str);
		++i;
	}
	return (NULL);
}

static char	*get_cmd_path(const char *cmd)
{
	struct stat	buf;
	const char	*path;
	char		*absolute;
	char		**dirs;

	if (stat(cmd, &buf) == 0)
		return (ft_strdup(cmd));
	path = ft_getenv("PATH");
	if (!path || *cmd == '.' | *cmd == '/')
	{
		pset_err(SHELL_NAME, cmd, strerror(errno), ENVIRONMENT_ERR);
		return (NULL);
	}
	dirs = ft_split(path, ':');
	absolute = find_cmd(dirs, cmd);
	if (!absolute)
		pset_err(SHELL_NAME, cmd, CMD_NOT_FOUND, ENVIRONMENT_ERR);
	ft_free_strarr(dirs);
	return (absolute);
}

void	ft_cmd(t_node *node)
{
	char	*path;
	pid_t	pid;
	int		wstatus;

	path = get_cmd_path(node->argv[0]);
	if (!path)
		return ;
	ft_strarr_replace(node->argv, path, 0);
	pid = fork();
	if (pid == -1)
		return (pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR));
	signal(SIGINT, child_proc_interrupt);
	signal(SIGQUIT, child_proc_quit);
	if (pid == 0 && execve(node->argv[0], node->argv, g_mini.env) == -1)
		pset_err(SHELL_NAME, NULL, strerror(errno), GENERIC_ERR);
	waitpid(pid, &wstatus, 0);
	signal(SIGINT, newline);
	signal(SIGQUIT, SIG_IGN);
	if (WIFEXITED(wstatus))
		g_mini.code = WEXITSTATUS(wstatus);
}