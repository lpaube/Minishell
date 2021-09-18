/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:29:29 by laube             #+#    #+#             */
/*   Updated: 2021/09/17 22:06:12 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parse.h"
#include "execution.h"

int	execution_control(t_node *node)
{
	if (ft_strncmp(node->cmd, "echo", 5) == 0)
		ft_echo(node);
	else if (ft_strncmp(node->cmd, "pwd", 4) == 0)
		ft_pwd(node);
	else if (ft_strncmp(node->cmd, "cd", 3) == 0)
		ft_cd(node);
	else if (ft_strncmp(node->cmd, "env", 4) == 0)
		ft_env(node);
	else if (ft_strncmp(node->cmd, "unset", 6) == 0)
		ft_unset(node);
	else if (ft_strncmp(node->cmd, "export", 7) == 0)
		ft_export(node);
	else if (ft_strncmp(node->cmd, "exit", 5) == 0)
	{
		ft_exit(node);
		return (1);
	}
	else
		ft_cmd(node);
	return (0);
}

int	main_control(t_node *node)
{
	while (node)
	{
		if (node->cmd)
			node->cmd = interpolate(node->cmd);
		interpolate_arr(node->args);
		interpolate_redirs(node->redirs);
		// if (operation_control() == 1)
		// 	return (1);
		if (node->cmd)
			execution_control(node);
		node = node->next;
	}
	return (0);
}
