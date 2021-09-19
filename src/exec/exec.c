/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:29:29 by laube             #+#    #+#             */
/*   Updated: 2021/09/19 00:16:16 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parse.h"
#include "minishell.h"
#include "exec.h"

static bool	dispatch_cmd(t_node *node)
{
	if (ft_strncmp(node->argv[0], "echo", 5) == 0)
		ft_echo(node);
	else if (ft_strncmp(node->argv[0], "pwd", 4) == 0)
		ft_pwd(node);
	else if (ft_strncmp(node->argv[0], "cd", 3) == 0)
		ft_cd(node);
	else if (ft_strncmp(node->argv[0], "env", 4) == 0)
		ft_env(node);
	else if (ft_strncmp(node->argv[0], "unset", 6) == 0)
		ft_unset(node);
	else if (ft_strncmp(node->argv[0], "export", 7) == 0)
		ft_export(node);
	else if (ft_strncmp(node->argv[0], "exit", 5) == 0)
		return (ft_exit(node));
	else
		ft_cmd(node);
	return (false);
}

bool	execute(t_node *node)
{
	if (node->argv[0])
		node->argv[0] = interpolate(node->argv[0]);
	interpolate_arr(node->argv);
	interpolate_redirs(node->redirs);
	if (node->argv[0] && dispatch_cmd(node))
		return (true);
	return (false);
}

bool	process_cmd(t_node *cmds)
{
	while (cmds)
	{
		if (execute(cmds) && !cmds->next)
			return (true);
		cmds = cmds->next;
	}
	return (false);
}
