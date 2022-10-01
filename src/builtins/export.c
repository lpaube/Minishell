#include "builtin.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

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
	if (ft_strarr_size(node->argv) == 1)
	{
		ft_env(node);
		return ;
	}
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
