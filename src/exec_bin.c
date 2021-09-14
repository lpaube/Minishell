/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:16:38 by laube             #+#    #+#             */
/*   Updated: 2021/09/14 13:25:46 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*validate_path(char *path, char *cmd)
{
	char		**paths;
	char		*tmp_path;
	char		*tentative_binpath;
	struct stat	buff;

	path = ft_strchr(path, '=') + 1;
	paths = ft_split(path, ':');
	while (*paths)
	{
		tmp_path = ft_strjoin(*paths, "/");
		tentative_binpath = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (stat(tentative_binpath, &buff) == 0)
		{
			ft_free_strarr(paths);
			return (tentative_binpath);
		}
		free(tentative_binpath);
		paths++;
	}
	ft_free_strarr(paths);
	return (NULL);
}

/*	Finds the PATH variable,
	then returns the full binary path of the binary */
char	*get_bin_path(char **envp, char *cmd)
{
	char	*path;

	while (*envp)
	{
		path = ft_strnstr(*envp, "PATH=", 5);
		if (path != NULL)
			return (validate_path(path, cmd));
		envp++;
	}
	return (NULL);
}
