/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:11:05 by laube             #+#    #+#             */
/*   Updated: 2021/09/08 18:36:56 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_cd(void)
{
	if (g_minishell.phrase->args[1] != NULL && g_minishell.phrase->args[2] != NULL)
		print_error("cd: too many arguments");
	if (chdir(g_minishell.phrase->args[1]) == -1)
		print_error("Could not change directory.");
}

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];
	if (getcwd(cwd, PATH_MAX) != NULL)
		printf("%s\n", cwd);
	else
		print_error("Could not get current directory.");
}

void	ft_export(void)
{
	char	*var_name;
	char	*equal_char;
	int		i;

	var_name = ft_strdup(g_minishell.phrase->args[1]);
	equal_char = ft_strchr(var_name, '=') + 1;
	if (!equal_char)
		print_error("Invalid export command: no equal sign found.");
	else
		*equal_char = 0;

	// Checks if var currently exists
	i = 0;
	while (g_minishell.env[i])
	{
		if (ft_strnstr(g_minishell.env[i], var_name, ft_strlen(var_name)))
		{
			free(g_minishell.env[i]);
			g_minishell.env[i] = g_minishell.phrase->args[1];
			return ;
		}
		i++;
	}
	// If var doesn't already exist: add new env var
	g_minishell.env = dup_env_table(g_minishell.env, g_minishell.phrase, 1);
}

void	ft_unset(void)
{
	int	i;
	int	j;

	i = 1;
	while (g_minishell.phrase->args[i])
	{
		g_minishell.phrase->args[i] = ft_strjoin(g_minishell.phrase->args[i], "=");
		j = 0;
		while (g_minishell.env[j])
		{
			if (ft_strnstr(g_minishell.env[j], g_minishell.phrase->args[i], ft_strlen(g_minishell.phrase->args[i])))
			{
				free(g_minishell.env[j]);
				while(g_minishell.env[j + 1])
				{
					g_minishell.env[j] = g_minishell.env[j + 1];
					j++;
				}
				g_minishell.env[j] = NULL;
				free(g_minishell.env[j + 1]);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_minishell.env[i])
	{
		printf("%s\n", g_minishell.env[i]);
		i++;
	}
}
