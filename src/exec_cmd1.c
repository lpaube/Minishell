/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:11:05 by laube             #+#    #+#             */
/*   Updated: 2021/08/31 00:28:11 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_header.h"

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

void	ft_unset(t_phrase *phrase)
{
	int	i;
	int	j;

	i = 1;
	while (phrase->cmd_args[i])
	{
		phrase->cmd_args[i] = ft_append_str(&phrase->cmd_args[i], '=');
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
