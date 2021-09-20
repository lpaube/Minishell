/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:36:30 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/20 03:56:57 by mleblanc         ###   ########.fr       */
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
	size_t		i;
	t_string	var_cpy;

	var_cpy = ft_str_new(var_name(var));
	ft_str_add_back(var_cpy, '=');
	i = 0;
	while (g_mini.env[i])
	{
		if (ft_str_cmp_cstr(var_cpy, g_mini.env[i], ft_str_len(var_cpy)) == 0)
		{
			free(g_mini.env[i]);
			ft_str_free(var_cpy);
			g_mini.env[i] = ft_strdup(var);
			return ;
		}
		++i;
	}
	ft_str_free(var_cpy);
	g_mini.env = ft_strarr_extend(g_mini.env, ft_strdup(var));
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
