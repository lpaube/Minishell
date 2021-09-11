/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:29:29 by laube             #+#    #+#             */
/*   Updated: 2021/09/10 19:28:30 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"



void	execution_control(t_phrase *phrase)
{
	if (ft_strnstr(phrase->name, "echo", 5))
	{
		ft_echo(phrase);
	}
	else if (ft_strnstr(phrase->name, "cd", 3))
	{
		ft_cd(phrase);
	}
	else if (ft_strnstr(phrase->name, "pwd", 4))
	{
		ft_pwd(phrase);
	}
	else if (ft_strnstr(phrase->name, "export", 7))
	{
		ft_export(phrase);
	}
	else if (ft_strnstr(phrase->name, "unset", 6))
	{
		ft_unset(phrase);
	}
	else if (ft_strnstr(phrase->name, "env", 4))
	{
		ft_env(phrase);
	}
	/* Doesn't currently handle arguments */
	else if (ft_strnstr(phrase->name, "exit", 5))
	{
		ft_exit(phrase);
	}
	else
	{
		ft_binary(phrase);
	}
}

/* Most functions don't correctly handle arguments of size 0 or > 1 */
int	main_control(t_phrase *phrase)
{
	g_minishell.phrase = phrase;
	while (g_minishell.phrase)
	{
		/*
		printf("1name: %s\n", g_minishell.phrase->name);
		printf("1next->name: %s\n", g_minishell.phrase->next->name);
		printf("1next->address: %p\n", g_minishell.phrase->next);
		*/
		g_minishell.phrase->name = parse_special_chars(g_minishell.phrase->name);
		parse_special_chars_arr(g_minishell.phrase->args);
		
		/*
		printf("2name: %s\n", g_minishell.phrase->name);
		if (g_minishell.phrase->next)
		{
			printf("2next->name: %s\n", g_minishell.phrase->next->name);
			printf("2next->address: %p\n", g_minishell.phrase->next);
		}
		*/
		operation_control();

		g_minishell.phrase = g_minishell.phrase->next;
	}

	return (0);
}
