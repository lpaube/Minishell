/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:33:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 21:51:03 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "print.h"
#include "env_variables.h"
#include <sys/errno.h>
#include <stdlib.h>

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
	if (ft_strarr_size(node->args) == 2)
	{
		if (chdir(node->args[1]) == -1)
		{
			free(oldpwd);
			return (print_error(CD, strerror(errno), node->args[1]));
		}
	}
	else if (ft_getenv("HOME") && chdir(ft_getenv("HOME")) == -1)
	{
		free(oldpwd);
		return (print_error(CD, NULL, strerror(errno)));
	}
	update_pwd(oldpwd);
	free(oldpwd);
}
