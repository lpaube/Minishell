/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:11:05 by laube             #+#    #+#             */
/*   Updated: 2021/09/13 13:18:03 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_cd(t_phrase *phrase)
{
	if (phrase->args[1] != NULL && phrase->args[2] != NULL)
		print_error("cd: too many arguments");
	if (chdir(phrase->args[1]) == -1)
		print_error("Could not change directory.");
}

void	ft_pwd(t_phrase *phrase)
{
	char	cwd[4096];

	(void)phrase;
	if (getcwd(cwd, 4096) != NULL)
		printf("%s\n", cwd);
	else
		print_error("Could not get current directory.");
}

void	ft_export(t_phrase *phrase)
{
	char	*var_name;
	char	*equal_char;
	int		i;

	var_name = ft_strdup(phrase->args[1]);
	equal_char = ft_strchr(var_name, '=') + 1;
	if (!equal_char)
		print_error("Invalid export command: no equal sign found.");
	else
		*equal_char = 0;
	i = 0;
	while (g_minishell.env[i])
	{
		if (ft_strnstr(g_minishell.env[i], var_name, ft_strlen(var_name)))
		{
			free(g_minishell.env[i]);
			g_minishell.env[i] = phrase->args[1];
			return ;
		}
		i++;
	}
	g_minishell.env = dup_env_table(g_minishell.env, phrase, 1);
}

void	ft_unset(t_phrase *phrase)
{
	int	i;
	int	j;

	i = 0;
	while (phrase->args[++i])
	{
		phrase->args[i] = ft_strjoin(phrase->args[i], "=");
		j = -1;
		while (g_minishell.env[++j])
		{
			if (ft_strnstr(g_minishell.env[j], phrase->args[i],
					ft_strlen(phrase->args[i])))
			{
				free(g_minishell.env[j]);
				while (g_minishell.env[j + 1])
				{
					g_minishell.env[j] = g_minishell.env[j + 1];
					j++;
				}
				g_minishell.env[j] = NULL;
				free(g_minishell.env[j + 1]);
				break ;
			}
		}
	}
}

void	ft_env(t_phrase *phrase)
{
	int	i;

	(void)phrase;
	i = 0;
	while (g_minishell.env[i])
	{
		printf("%s\n", g_minishell.env[i]);
		i++;
	}
}
