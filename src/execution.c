/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:50:36 by laube             #+#    #+#             */
/*   Updated: 2021/08/18 14:52:25 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct s_parse
{
	int	bin;
	char	**env;
	char	*cmd;
	char	**cmd_args; // Needs to start with bin name, and be NULL terminated
} t_parse;

char	*validate_path(char *path, char *cmd)
{
	char	**paths;
	char	*tmp_path;
	char	*tentative_binpath;
	struct stat	buff;

	path = ft_strchr(path, '=') + 1;
	paths = ft_split(path, ':');
	while (*paths)
	{
		tmp_path = ft_strjoin(*paths, "/");
		tentative_binpath = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (stat(tentative_binpath, &buff) == 0)
			return (tentative_binpath);
		free(tentative_binpath);
		paths++;
	}
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

/*	Executes the binary entered as cmd */
int	ft_binary(t_parse *parse)
{
	char	*bin_path;
	pid_t	pid;

	bin_path = get_bin_path(parse->env, parse->cmd);
	if (bin_path == NULL)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		execve(bin_path, parse->cmd_args, parse->env);
	}
	wait(0);
	return (0);
}

int	execution_control(t_parse *parse)
{
	if (parse->bin == 1)
		ft_binary(parse);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_parse	*parse;
	char *test_args[3] = {"ls", "-l", NULL};

	parse = malloc(sizeof(*parse));
	parse->bin = 1;
	parse->env = env;
	parse->cmd = "ls";
	parse->cmd_args = test_args;
	// This function will take whatever Michael gives it after parsing
	execution_control(parse);

	return (0);
}