/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:50:36 by laube             #+#    #+#             */
/*   Updated: 2021/08/22 01:17:32 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include "../libft/libft.h"

typedef struct s_parse
{
	int	bin;
	char	**env;
	char	*cmd;
	char	**cmd_args; // Needs to start with bin name, and be NULL terminated
} t_parse;

void	ft_terminate(int err, char *err_str)
{
	char	*ret_str;

	if (err != 0)
		ret_str = strerror(err);
	else
		ret_str = err_str;
	printf("%s\n", err_str);
	exit(0);
}

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
		ft_terminate(errno, "Invalid process id after fork.");
	if (pid == 0)
	{
		if (execve(bin_path, parse->cmd_args, parse->env) == -1)
			ft_terminate(errno, "Invalid execution of binary.");
	}
	wait(0);
	return (0);
}

void	ft_echo(t_parse *parse)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (ft_strnstr((parse->cmd_args)[i], "-n", 2))
	{
		nl = 0;
		i++;
	}
	while ((parse->cmd_args)[i])
	{
		printf("%s", (parse->cmd_args[i]));
		i++;
		if ((parse->cmd_args)[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
}

void	ft_cd(t_parse *parse)
{
	int	ret;
	
	if (parse->cmd_args[1] != NULL && parse->cmd_args[2] != NULL)
		ft_terminate(errno, "cd: too many arguments");
	if (chdir(parse->cmd_args[1]) == -1)
		ft_terminate(errno, "Could not change directory.");
}

void	ft_pwd(t_parse *parse)
{
	char	cwd[PATH_MAX];
	if (getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
		ft_terminate(errno, "Could not get current directory.");
}

/*	Returns a malloc'd 2d duplicated table of env
 *	and updates it with new var if applicable	*/
char	**dup_env_table(char **table, t_parse *parse, int new_var)
{
	char	**res_table;
	int		i;
	char	*new_arg;

	new_arg = parse->cmd_args[1];
	i = 0;
	while (table[i])
		i++;
	res_table = malloc((i + 1 + new_var) * sizeof(char *));
	if (!res_table)
		ft_terminate(errno, "Could not malloc 'res_table'.");
	i = 0;
	while (table[i])
	{
		res_table[i] = malloc((ft_strlen(table[i]) + 1) * sizeof(char));
		if (!res_table[i])
			ft_terminate(errno, "Could not malloc 'res_table[i]");
		ft_memcpy(res_table[i], table[i], ft_strlen(table[i]) + 1);
		i++;
	}
	if (new_var)
	{
		res_table[i] = malloc((ft_strlen(new_arg) * sizeof(char)));
		ft_memcpy(res_table[i], new_arg, ft_strlen(new_arg) + 1);
		i++;
	}
	table[i] = NULL;
	return (res_table);
}

void	ft_export(t_parse *parse)
{
	char	*var_name;
	char	*equal_char;
	int		i;

	var_name = ft_strdup(parse->cmd_args[1]);
	equal_char = ft_strchr(var_name, '=') + 1;
	if (!equal_char)
		ft_terminate(errno, "Invalid export command: no equal sign found.");
	else
		*equal_char = 0;

	// Checks if var currently exists
	i = 0;
	while (parse->env[i])
	{
		if (ft_strnstr(parse->env[i], var_name, ft_strlen(var_name)))
		{
			free(parse->env[i]);
			parse->env[i] = parse->cmd_args[1];
			return ;
		}
		i++;
	}
	// If var doesn't already exist: add new env var
	parse->env = dup_env_table(parse->env, parse, 1);
}

/*	Receives a malloc'd str, and returns a new malloc'd str
 *	with appended char	*/
char	*ft_append_str(char **str, char c)
{
	char	*new_str;
	int		i;

	printf("here1\n");
	new_str = malloc((ft_strlen(*str) + 1) * sizeof(char));
	i = 0;
	while ((*str)[i])
	{
		new_str[i] = (*str)[i];
		i++;
	}
	printf("here2\n");
	new_str[i] = c;
	i++;
	new_str[i] = 0;
	printf("here3\n");
	printf("HEY: %s\n", *str);
	//free(*str);
	printf("here4\n");
	return (new_str);
}

void	ft_unset(t_parse *parse)
{
	int	i;
	int	j;

	i = 1;
	printf("ok1\n");
	while (parse->cmd_args[i])
	{
		printf("ok2\n");
		parse->cmd_args[i] = ft_append_str(&parse->cmd_args[i], '=');
		printf("ok3\n");
		j = 0;
		while (parse->env[j])
		{
			if (ft_strnstr(parse->env[j], parse->cmd_args[i], ft_strlen(parse->cmd_args[i])))
			{
				free(parse->env[j]);
				while(parse->env[j + 1])
				{
					parse->env[j] = parse->env[j + 1];
					j++;
				}
				parse->env[j] = NULL;
				free(parse->env[j + 1]);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_env(t_parse *parse)
{
	int	i;

	i = 0;
	while (parse->env[i])
	{
		printf("%s\n", parse->env[i]);
		i++;
	}
}

void	ft_exit(t_parse *parse)
{
	exit(0);
}

/* Most functions don't correctly handle arguments of size 0 or > 1 */
int	execution_control(t_parse *parse)
{
	if (parse->bin == 1)
		ft_binary(parse);
	else if (ft_strnstr(parse->cmd, "echo", 4))
	{
		ft_echo(parse);
	}
	else if (ft_strnstr(parse->cmd, "cd", 2))
	{
		ft_cd(parse);
	}
	else if (ft_strnstr(parse->cmd, "pwd", 3))
	{
		ft_pwd(parse);
	}
	else if (ft_strnstr(parse->cmd, "export", 6))
	{
		ft_export(parse);
	}
	else if (ft_strnstr(parse->cmd, "unset", 5))
	{
		ft_unset(parse);
	}
	else if (ft_strnstr(parse->cmd, "env", 3))
	{
		ft_env(parse);
	}
	/* Doesn't currently handle arguments */
	else if (ft_strnstr(parse->cmd, "exit", 4))
	{
		ft_exit(parse);
	}
	return (0);
}


/*	Prints a 2d table of char
 *	for testing purposes	*/
void	put_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		printf("%s\n", table[i]);
		i++;
	}
}

/*	t_parse parse will be replaced by the struct passed by Mik	*/
int	main(int argc, char **argv, char **env)
{
	errno = 0;
	t_parse	*parse;
	char *test_args[3] = {"env", NULL, NULL};

	parse = malloc(sizeof(*parse));
	parse->bin = 0;
	parse->cmd = "env";
	parse->cmd_args = test_args;
	parse->env = dup_env_table(env, parse, 0);

	execution_control(parse);
	//put_table(parse->env);

	return (0);
}
