/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:29:29 by laube             #+#    #+#             */
/*   Updated: 2021/09/15 13:04:33 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execution_control(t_phrase *phrase)
{
	if (!phrase)
		return (0);
	if (ft_strnstr(phrase->name, "echo", 5))
		ft_echo(phrase);
	else if (ft_strnstr(phrase->name, "cd", 3))
		ft_cd(phrase);
	else if (ft_strnstr(phrase->name, "pwd", 4))
		ft_pwd(phrase);
	else if (ft_strnstr(phrase->name, "export", 7))
		ft_export(phrase->args[1]);
	else if (ft_strnstr(phrase->name, "unset", 6))
		ft_unset(phrase);
	else if (ft_strnstr(phrase->name, "env", 4))
		ft_env();
	else if (ft_strnstr(phrase->name, "exit", 5))
	{
		ft_exit(phrase);
		return (1);
	}
	else
		ft_binary(phrase);
	return (0);
}

int	main_control(t_phrase *phrase)
{
	g_minishell.phrase = phrase;
	while (g_minishell.phrase)
	{
		g_minishell.phrase->name = parse_spec_char(g_minishell.phrase->name);
		parse_special_chars_arr(g_minishell.phrase->args);
		if (operation_control() == 1)
			return (1);
		g_minishell.phrase = g_minishell.phrase->next;
	}
	return (0);
}
