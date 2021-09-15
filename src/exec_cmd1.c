/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:11:05 by laube             #+#    #+#             */
/*   Updated: 2021/09/14 18:35:19 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_cd(t_node *phrase)
{
	char	*tmp_pwd;
	char	*my_pwd;

	if (phrase->args[1] != NULL && phrase->args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
	}
	else if (phrase->args[1] == NULL)
	{
		chdir(ft_getenv("HOME"));
	}
	else if (chdir(phrase->args[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(phrase->args[1], 2);
		ft_putstr_fd("\n", 2);
	}
	tmp_pwd = getcwd(NULL, 0);
	my_pwd = ft_strjoin("PWD=", tmp_pwd);
	ft_export(my_pwd);
	free(tmp_pwd);
	return ;
}

void	ft_pwd(t_node *phrase)
{
	char	cwd[4096];

	(void)phrase;
	if (getcwd(cwd, 4096) != NULL)
		printf("%s\n", cwd);
	else
		print_error("Could not get current directory.");
}

int	ft_export(char *env_var)
{
	char	*var_name;
	char	*equal_char;
	int		i;

	if (!env_var)
		return ft_env();
	var_name = ft_strdup(env_var);
	equal_char = ft_strchr(var_name, '=') + 1;
	if (!equal_char)
		print_error("Invalid export command: no equal sign found.");
	else
		*equal_char = 0;
	i = -1;
	while (g_minishell.env[++i])
	{
		if (ft_strnstr(g_minishell.env[i], var_name, ft_strlen(var_name)))
		{
			free(g_minishell.env[i]);
			g_minishell.env[i] = env_var;
			free(var_name);
			return (0);
		}
	}
	g_minishell.env = dup_env_table(g_minishell.env, env_var, 1);
	free(var_name);
	return (0);
}

void	ft_unset(t_node *phrase)
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

int	ft_env(void)
{
	int	i;

	i = 0;
	while (g_minishell.env[i])
	{
		printf("%s\n", g_minishell.env[i]);
		i++;
	}
	return (0);
}
