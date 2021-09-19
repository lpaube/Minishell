/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:34:03 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/19 00:14:19 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include <stdio.h>

void	ft_env(t_node *node)
{
	size_t	i;

	if (ft_strarr_size(node->argv) > 1)
		return (pset_err(ENV, NULL, TOO_MANY_ARGS, GENERIC_ERR));
	i = 0;
	while (g_mini.env[i])
	{
		printf("%s\n", g_mini.env[i]);
		++i;
	}
	g_mini.code = SUCCESS;
}