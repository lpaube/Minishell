/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:36:30 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/27 16:31:01 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

static void	show_env(void)
{
	size_t	i;

	i = 0;
	while (g_mini.env[i])
	{
		printf("declare -x %s\n", g_mini.env[i]);
		++i;
	}
}

static void	add_var(const char *var)
{
	t_string	var_cpy;
	const char	*value;

	var_cpy = ft_str_new(var_name(var));
	value = ft_strchr(var, '=') + 1;
	ft_setenv(ft_str_data(var_cpy), value);
	ft_str_free(var_cpy);
}

void	ft_export(t_node *node)
{
	size_t	i;
	char	*var;

	g_mini.code = SUCCESS;
	if (ft_strarr_size(node->argv) < 2)
		return (show_env());
	var = NULL;
	i = 1;
	while (node->argv[i])
	{
		free(var);
		var = var_name(node->argv[i]);
		if (!is_valid_var_name(var))
		{
			pset_err(EXPORT, node->argv[i], BAD_IDENT, GENERIC_ERR);
			++i;
			continue ;
		}
		add_var(node->argv[i]);
		++i;
	}
	free(var);
}
