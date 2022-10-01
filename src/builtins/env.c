#include "builtin.h"
#include "minishell.h"
#include <stdio.h>

void	ft_env(t_node *node)
{
	size_t	i;

	if (ft_strarr_size(node->argv) > 1)
	{
		pset_err(ENV, NULL, TOO_MANY_ARGS, GENERIC_ERR);
		return ;
	}
	i = 0;
	while (g_mini.env[i])
	{
		ft_putendl_fd(g_mini.env[i], STDOUT_FILENO);
		++i;
	}
	g_mini.code = SUCCESS;
}
