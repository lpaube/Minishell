/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:44:29 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/16 14:02:56 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "minishell.h"
#include <stdlib.h>

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
		ft_printf("%s", (node->args)[i]);
		++i;
		if ((node->args)[i])
			ft_printf(" ");
	}
	if (nl)
		ft_printf("\n");
}

void	ft_pwd(void)
{
	char	cwd[CWD_BUFFER_SIZE];

	if (getcwd(cwd, CWD_BUFFER_SIZE) != NULL)
		ft_printf("%s\n", cwd);
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
	while (g_minishell.env[i])
	{
		ft_printf("%s\n", g_minishell.env[i]);
		++i;
	}
}

void	ft_unset(t_node *node)
{
	size_t		i;
	t_string	var;

	if (ft_strarr_size(node->args) < 2)
		return (print_error("unset: not enough arguments", NULL));
	if (!is_valid_var_name(node->args[1]))
		return (print_error("unset: invalid parameter name: ", node->args[1]));
	var = ft_str_new_copy(node->args[1]);
	ft_str_add_back(var, '=');
	i = 0;
	while (g_minishell.env[i])
	{
		if (ft_str_cmp_cstr(var, g_minishell.env[i], ft_str_len(var)) == 0)
		{
			ft_shrink_strarr(g_minishell.env, i);
			ft_str_free(var);
			return ;
		}
		++i;
	}
	ft_str_free(var);
}
