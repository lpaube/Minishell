/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 22:25:41 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 18:07:05 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "print.h"
#include "env.h"
#include <stdlib.h>

#define CWD_BUFFER_SIZE (4096)

void	add_var(const char *var)
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

static void	process_error(const char *prg, const char *v1,
	const char *v2, bool *can_print)
{
	if (*can_print)
	{
		print_error(prg, v1, v2);
		*can_print = false;
	}
}

void	ft_export(t_node *node)
{
	size_t	i;
	bool	can_perror;
	char	*var;

	if (ft_strarr_size(node->args) < 2)
		return (ft_env());
	var = NULL;
	can_perror = true;
	i = 1;
	while (node->args[i])
	{
		free(var);
		var = var_name(node->args[i]);
		if (!is_valid_var_name(var))
		{
			process_error(EXPORT, "not valid in this context", node->args[i],
				&can_perror);
			++i;
			continue ;
		}
		add_var(node->args[i]);
		++i;
	}
	free(var);
}

static void	remove_var(const char *var)
{
	size_t		i;
	t_string	var_cpy;

	var_cpy = ft_str_new_copy(var);
	ft_str_add_back(var_cpy, '=');
	i = 0;
	while (g_mini.env[i])
	{
		if (ft_str_cmp_cstr(var_cpy, g_mini.env[i], ft_str_len(var_cpy)) == 0)
		{
			ft_shrink_strarr(g_mini.env, i);
			ft_str_free(var_cpy);
			return ;
		}
		++i;
	}
	ft_str_free(var_cpy);
}

void	ft_unset(t_node *node)
{
	size_t	i;
	bool	can_perror;

	if (ft_strarr_size(node->args) < 2)
		return (print_error(UNSET, NULL, "not enough arguments"));
	can_perror = true;
	i = 1;
	while (node->args[i])
	{
		if (!is_valid_var_name(node->args[i]))
		{
			process_error(UNSET, node->args[i], "invalid parameter name",
				&can_perror);
			++i;
			continue ;
		}
		remove_var(node->args[i]);
		++i;
	}
}
