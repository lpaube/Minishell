/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:34:03 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/18 06:22:03 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include <stdio.h>

void	ft_env(t_node *node)
{
	size_t	i;

	if (ft_strarr_size(node->args) > 1)
		return (pset_err(ENV, NULL, "too many arguments", GENERIC_ERR));
	i = 0;
	while (g_mini.env[i])
	{
		printf("%s\n", g_mini.env[i]);
		++i;
	}
	g_mini.code = SUCCESS;
}
