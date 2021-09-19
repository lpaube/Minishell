/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:33:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/19 00:14:19 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include <string.h>
#include <sys/errno.h>
#include <stdlib.h>

static void	update_pwd(const char *oldpwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (pset_err(CD, NULL, strerror(errno), GENERIC_ERR));
	ft_setenv(ENV_OLDPWD, oldpwd);
	ft_setenv(ENV_PWD, cwd);
	free(cwd);
	g_mini.code = SUCCESS;
}

void	ft_cd(t_node *node)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (pset_err(CD, NULL, strerror(errno), GENERIC_ERR));
	if (ft_strarr_size(node->argv) > 1)
	{
		if (chdir(node->argv[1]) == -1)
		{
			free(oldpwd);
			return (pset_err(CD, strerror(errno), node->argv[1], GENERIC_ERR));
		}
	}
	else if (!ft_getenv(ENV_HOME))
	{
		free(oldpwd);
		return (pset_err(CD, NULL, NO_HOME, GENERIC_ERR));
	}
	else if (chdir(ft_getenv(ENV_HOME)) == -1)
	{
		free(oldpwd);
		return (pset_err(CD, NULL, strerror(errno), GENERIC_ERR));
	}
	update_pwd(oldpwd);
	free(oldpwd);
}
