/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:50:36 by laube             #+#    #+#             */
/*   Updated: 2021/08/24 15:36:30 by laube            ###   ########.fr       */
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

typedef struct s_phrase
{
	int	bin;
	char	**env;
	char	*cmd;
	char	**cmd_args; // Needs to start with bin name, and be NULL terminated
} t_phrase;

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
int	ft_binary(t_phrase *phrase)
{
	char	*bin_path;
	pid_t	pid;

	bin_path = get_bin_path(phrase->env, phrase->cmd);
	if (bin_path == NULL)
		return (-1);
	pid = fork();
	if (pid == -1)
		ft_terminate(errno, "Invalid process id after fork.");
	if (pid == 0)
	{
		if (execve(bin_path, phrase->cmd_args, phrase->env) == -1)
			ft_terminate(errno, "Invalid execution of binary.");
	}
	wait(0);
	return (0);
}

void	ft_echo(t_phrase *phrase)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (ft_strnstr((phrase->cmd_args)[i], "-n", 2))
	{
		nl = 0;
		i++;
	}
	while ((phrase->cmd_args)[i])
	{
		printf("%s", (phrase->cmd_args[i]));
		i++;
		if ((phrase->cmd_args)[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
}

void	ft_cd(t_phrase *phrase)
{
	int	ret;
	
	if (phrase->cmd_args[1] != NULL && phrase->cmd_args[2] != NULL)
		ft_terminate(errno, "cd: too many arguments");
	if (chdir(phrase->cmd_args[1]) == -1)
		ft_terminate(errno, "Could not change directory.");
}

void	ft_pwd(t_phrase *phrase)
{
	char	cwd[PATH_MAX];
	if (getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
		ft_terminate(errno, "Could not get current directory.");
}

/*	Returns a malloc'd 2d duplicated table of env
 *	and updates it with new var if applicable	*/
char	**dup_env_table(char **table, t_phrase *phrase, int new_var)
{
	char	**res_table;
	int		i;
	char	*new_arg;

	new_arg = phrase->cmd_args[1];
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

void	ft_export(t_phrase *phrase)
{
	char	*var_name;
	char	*equal_char;
	int		i;

	var_name = ft_strdup(phrase->cmd_args[1]);
	equal_char = ft_strchr(var_name, '=') + 1;
	if (!equal_char)
		ft_terminate(errno, "Invalid export command: no equal sign found.");
	else
		*equal_char = 0;

	// Checks if var currently exists
	i = 0;
	while (phrase->env[i])
	{
		if (ft_strnstr(phrase->env[i], var_name, ft_strlen(var_name)))
		{
			free(phrase->env[i]);
			phrase->env[i] = phrase->cmd_args[1];
			return ;
		}
		i++;
	}
	// If var doesn't already exist: add new env var
	phrase->env = dup_env_table(phrase->env, phrase, 1);
}

/*	Receives a malloc'd str, and returns a new malloc'd str
 *	with appended char	*/
char	*ft_append_str(char **str, char c)
{
	char	*new_str;
	int		i;

	new_str = malloc((ft_strlen(*str) + 1) * sizeof(char));
	i = 0;
	while ((*str)[i])
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = c;
	i++;
	new_str[i] = 0;
	printf("HEY: %s\n", *str);
	//free(*str);
	return (new_str);
}

void	ft_unset(t_phrase *phrase)
{
	int	i;
	int	j;

	i = 1;
	printf("ok1\n");
	while (phrase->cmd_args[i])
	{
		printf("ok2\n");
		phrase->cmd_args[i] = ft_append_str(&phrase->cmd_args[i], '=');
		printf("ok3\n");
		j = 0;
		while (phrase->env[j])
		{
			if (ft_strnstr(phrase->env[j], phrase->cmd_args[i], ft_strlen(phrase->cmd_args[i])))
			{
				free(phrase->env[j]);
				while(phrase->env[j + 1])
				{
					phrase->env[j] = phrase->env[j + 1];
					j++;
				}
				phrase->env[j] = NULL;
				free(phrase->env[j + 1]);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_env(t_phrase *phrase)
{
	int	i;

	i = 0;
	while (phrase->env[i])
	{
		printf("%s\n", phrase->env[i]);
		i++;
	}
}

void	ft_exit(t_phrase *phrase)
{
	exit(0);
}

/* Most functions don't correctly handle arguments of size 0 or > 1 */
int	execution_control(t_phrase *phrase)
{
	if (phrase->bin == 1)
		ft_binary(phrase);
	else if (ft_strnstr(phrase->cmd, "echo", 5))
	{
		ft_echo(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "cd", 3))
	{
		ft_cd(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "pwd", 4))
	{
		ft_pwd(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "export", 7))
	{
		ft_export(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "unset", 6))
	{
		ft_unset(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "env", 4))
	{
		ft_env(phrase);
	}
	/* Doesn't currently handle arguments */
	else if (ft_strnstr(phrase->cmd, "exit", 5))
	{
		ft_exit(phrase);
	}
	return (0);
}


//	t_phrase phrase will be replaced by the struct passed by Mik	*/
/*
int	main(int argc, char **argv, char **env)
{
	errno = 0;
	t_phrase	*phrase;
	char *test_args[3] = {"env", NULL, NULL};

	phrase = malloc(sizeof(*phrase));
	phrase->bin = 0;
	phrase->cmd = "env";
	phrase->cmd_args = test_args;
	phrase->env = dup_env_table(env, phrase, 0);

	execution_control(phrase);
	//put_table(phrase->env);

	return (0);
}
*/
