/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:44:29 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/16 22:30:23 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "minishell.h"
#include "print.h"
#include <stdlib.h>
#include <stdio.h>

#define CWD_BUFFER_SIZE (4096)

void	ft_echo(t_node *node)
{
	bool	nl;
	int		i;

	nl = true;
	i = 1;
	while ((node->args)[i] && ft_strncmp((node->args)[i], "-n", 3) == 0)
	{
		nl = false;
		++i;
	}
	while ((node->args)[i])
	{
		printf("%s", (node->args)[i]);
		++i;
		if ((node->args)[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
}

void	ft_pwd(void)
{
	char	cwd[CWD_BUFFER_SIZE];

	if (getcwd(cwd, CWD_BUFFER_SIZE) != NULL)
		printf("%s\n", cwd);
	else
		print_error("pwd: could not get current directory.", NULL);
}

void	ft_cd(t_node *node)
{
	char	*cwd;

	if (ft_strarr_size(node->args) > 2)
		print_error("cd: too many arguments", NULL);
	else if (ft_strarr_size(node->args) == 1)
		chdir(ft_getenv("HOME"));
	else if (chdir(node->args[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(node->args[1], STDERR_FILENO);
	}
	cwd = getcwd(NULL, 0);
	ft_setenv("PWD", cwd);
	free(cwd);
}

void	ft_env(void)
{
	size_t	i;

	i = 0;
	while (g_mini.env[i])
	{
		printf("%s\n", g_mini.env[i]);
		++i;
	}
}

void	ft_exit(t_node *node)
{
	(void)node;
}
