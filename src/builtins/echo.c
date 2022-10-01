#include "builtin.h"
#include "minishell.h"
#include <stdio.h>

void	ft_echo(t_node *node)
{
	bool	nl;
	int		i;

	nl = true;
	i = 1;
	while (node->argv[i] && ft_strncmp(node->argv[i], "-n", 3) == 0)
	{
		nl = false;
		++i;
	}
	while (node->argv[i])
	{
		ft_putstr_fd(node->argv[i], STDOUT_FILENO);
		++i;
		if (node->argv[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_mini.code = SUCCESS;
}
