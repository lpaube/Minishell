/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:16:38 by laube             #+#    #+#             */
/*   Updated: 2021/09/17 21:51:04 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "env_variables.h"
#include "print.h"
#include "minishell.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

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
		print_error(SHELL_NAME, strerror(errno), cmd);
		return (NULL);
	}
	dirs = ft_split(path, ':');
	absolute = find_cmd(dirs, cmd);
	if (!absolute)
		print_error(SHELL_NAME, strerror(errno), cmd);
	ft_free_strarr(dirs);
	return (absolute);
}

void	ft_cmd(t_node *node)
{
	char	*path;
	int		pid;

	path = get_cmd_path(node->cmd);
	if (!path)
		return ;
	pid = fork();
	if (pid == -1)
		print_error(SHELL_NAME, NULL, strerror(errno));
	if (pid == 0)
	{
		if (execve(path, node->args, g_mini.env) == -1)
			print_error(SHELL_NAME, NULL, strerror(errno));
		return ;
	}
	wait(NULL);
	free(path);
}
