/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:36:30 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/18 04:40:24 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "environment.h"
#include "eprint.h"
#include <stdlib.h>

#define CTX_ERR "not valid in this context"

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
	g_mini.env = ft_expand_strarr(g_mini.env, ft_strdup(var));
}

void	process_error(const char *prg, const char *v1, const char *v2,
	bool *can_print)
{
	if (*can_print)
	{
		pset_err(prg, v1, v2, GENERIC_ERR);
		*can_print = false;
	}
}

void	ft_export(t_node *node)
{
	size_t	i;
	bool	can_perror;
	char	*var;

	if (ft_strarr_size(node->args) < 2)
		return (ft_env(node));
	var = NULL;
	can_perror = true;
	i = 1;
	while (node->args[i])
	{
		free(var);
		var = var_name(node->args[i]);
		if (!is_valid_var_name(var))
		{
			process_error(EXPORT, CTX_ERR, node->args[i], &can_perror);
			++i;
			continue ;
		}
		add_var(node->args[i]);
		++i;
	}
	free(var);
	if (can_perror)
		g_mini.code = SUCCESS;
}
