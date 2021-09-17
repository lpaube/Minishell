/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:16:38 by laube             #+#    #+#             */
/*   Updated: 2021/09/16 22:17:24 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "env.h"
#include <sys/stat.h>
#include <stdlib.h>

// char	*validate_path(char *path, char *cmd)
// {
// 	char		**paths;
// 	int			i;
// 	char		*tmp_path;
// 	char		*tentative_binpath;
// 	struct stat	buff;

// 	path = ft_strchr(path, '=') + 1;
// 	paths = ft_split(path, ':');
// 	i = 0;
// 	while (paths[i])
// 	{
// 		tmp_path = ft_strjoin(paths[i], "/");
// 		tentative_binpath = ft_strjoin(tmp_path, cmd);
// 		free(tmp_path);
// 		if (stat(tentative_binpath, &buff) == 0)
// 		{
// 			ft_free_strarr(paths);
// 			return (tentative_binpath);
// 		}
// 		free(tentative_binpath);
// 		i++;
// 	}
// 	ft_free_strarr(paths);
// 	return (NULL);
// }

static char *find_cmd(char **dirs, const char *cmd)
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
	if (!path  || *cmd == '.')
		return (NULL);
	dirs = ft_split(path, ':');
	absolute = find_cmd(dirs, cmd);
	ft_free_strarr(dirs);
	return (absolute);
}

void ft_cmd(t_node *node)
{
	char	*path;

	path = get_cmd_path(node->cmd);
	ft_printf("%s\n", path);
	free(path);
}
