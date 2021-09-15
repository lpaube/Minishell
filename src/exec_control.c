/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:29:29 by laube             #+#    #+#             */
/*   Updated: 2021/09/15 10:50:49 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execution_control(t_node *phrase)
{
	if (ft_strnstr(phrase->prg, "echo", 5))
		ft_echo(phrase);
	else if (ft_strnstr(phrase->prg, "cd", 3))
		ft_cd(phrase);
	else if (ft_strnstr(phrase->prg, "pwd", 4))
		ft_pwd(phrase);
	else if (ft_strnstr(phrase->prg, "export", 7))
		ft_export(phrase->args[1]);
	else if (ft_strnstr(phrase->prg, "unset", 6))
		ft_unset(phrase);
	else if (ft_strnstr(phrase->prg, "env", 4))
		ft_env();
	else if (ft_strnstr(phrase->prg, "exit", 5))
	{
		ft_exit(phrase);
		return (1);
	}
	else
		ft_binary(phrase);
	return (0);
}

int	main_control(t_node *phrase)
{
	g_minishell.phrase = phrase;
	while (g_minishell.phrase)
	{
		// g_minishell.phrase->cmd = parse_spec_char(g_minishell.phrase->cmd);
		// parse_special_chars_arr(g_minishell.phrase->args);
		// if (operation_control() == 1)
		// 	return (1);
		g_minishell.phrase = g_minishell.phrase->next;
	}
	return (0);
}
