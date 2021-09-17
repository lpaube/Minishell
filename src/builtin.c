/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:44:29 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 19:11:50 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "minishell.h"
#include "print.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CWD_BUFFER_SIZE (1024)

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

void	ft_pwd(t_node *node)
{
	char	cwd[CWD_BUFFER_SIZE];

	if (ft_strarr_size(node->args) > 1)
		print_error(PWD, NULL, "too many arguments");
	else if (getcwd(cwd, CWD_BUFFER_SIZE) != NULL)
		printf("%s\n", cwd);
	else
		print_error(PWD, NULL, strerror(errno));
}

static void	update_pwd(const char *oldpwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (print_error(CD, NULL, strerror(errno)));
	ft_setenv("OLDPWD", oldpwd);
	ft_setenv("PWD", cwd);
	free(cwd);
}

void	ft_cd(t_node *node)
{
	char	*oldpwd;

	if (ft_strarr_size(node->args) > 2)
		return (print_error(CD, NULL, "too many arguments"));
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (print_error(CD, NULL, strerror(errno)));
	if (ft_strarr_size(node->args) == 1 && chdir(ft_getenv("HOME")) == -1)
	{
		free(oldpwd);
		return (print_error(CD, NULL, strerror(errno)));
	}
	else if (chdir(node->args[1]) == -1)
	{
		free(oldpwd);
		return (print_error(CD, strerror(errno), node->args[1]));
	}
	update_pwd(oldpwd);
	free(oldpwd);
}

void	ft_env(t_node *node)
{
	size_t	i;

	if (ft_strarr_size(node->args) > 1)
		return (print_error(ENV, NULL, "too many arguments"));
	i = 0;
	while (g_mini.env[i])
	{
		printf("%s\n", g_mini.env[i]);
		++i;
	}
}
