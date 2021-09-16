/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 22:25:41 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/16 14:07:08 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"
#include "builtin.h"
#include <stdlib.h>

#define CWD_BUFFER_SIZE (4096)

bool	is_valid_var_name(const char *var)
{
	char	*name;
	char	*ptr;
	bool	ret;

	name = var_name(var);
	if (!name)
		return (false);
	ptr = name;
	ret = true;
	while (*ptr)
	{
		if (!(ft_isalnum(*ptr) || *ptr == '_'))
		{
			ret = false;
			break ;
		}
		++ptr;
	}
	free(name);
	return (ret);
}

void	ft_export(t_node *node)
{
	t_string	var;
	size_t		i;

	if (ft_strarr_size(node->args) < 2)
		return (ft_env());
	if (!is_valid_var_name(node->args[1]))
		return (print_error("export: not valid in this context: ",
			node->args[1]));
	var = ft_str_new(var_name(node->args[1]));
	ft_str_add_back(var, '=');
	i = 0;
	while (g_minishell.env[i])
	{
		if (ft_str_cmp_cstr(var, g_minishell.env[i], ft_str_len(var)) == 0)
		{
			free(g_minishell.env[i]);
			ft_str_free(var);
			g_minishell.env[i] = ft_strdup(node->args[1]);
			return ;
		}
		++i;
	}
	g_minishell.env
		= ft_expand_strarr(g_minishell.env, ft_strdup(node->args[1]));
	ft_str_free(var);
}

void	ft_exit(t_node *node)
{
	(void)node;
}
