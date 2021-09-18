/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:32:32 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/18 04:32:11 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "eprint.h"
#include "minishell.h"
#include <stdio.h>

#define CWD_BUFFER_SIZE (1024)

void	ft_pwd(t_node *node)
{
	char	cwd[CWD_BUFFER_SIZE];

	if (ft_strarr_size(node->args) > 1)
		return (pset_err(PWD, NULL, "too many arguments", GENERIC_ERR));
	else if (getcwd(cwd, CWD_BUFFER_SIZE) != NULL)
		printf("%s\n", cwd);
	else
		return (pset_err(PWD, NULL, strerror(errno), GENERIC_ERR));
	g_mini.code = SUCCESS;
}
