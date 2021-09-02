/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:11:05 by laube             #+#    #+#             */
/*   Updated: 2021/09/02 14:16:41 by laube            ###   ########.fr       */
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
	(void)phrase;
	char	cwd[PATH_MAX];
	if (getcwd(cwd, PATH_MAX) != NULL)
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

	// Checks if var currently exists
	i = 0;
	while (my_env[i])
	{
		if (ft_strnstr(my_env[i], var_name, ft_strlen(var_name)))
		{
			free(my_env[i]);
			my_env[i] = phrase->args[1];
			return ;
		}
		i++;
	}
	// If var doesn't already exist: add new env var
	my_env = dup_env_table(my_env, phrase, 1);
}

void	ft_unset(t_phrase *phrase)
{
	int	i;
	int	j;

	i = 1;
	while (phrase->args[i])
	{
		phrase->args[i] = ft_append_str(&phrase->args[i], '=');
		j = 0;
		while (my_env[j])
		{
			if (ft_strnstr(my_env[j], phrase->args[i], ft_strlen(phrase->args[i])))
			{
				free(my_env[j]);
				while(my_env[j + 1])
				{
					my_env[j] = my_env[j + 1];
					j++;
				}
				my_env[j] = NULL;
				free(my_env[j + 1]);
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

	(void)phrase;
	i = 0;
	while (my_env[i])
	{
		printf("%s\n", my_env[i]);
		i++;
	}
}
