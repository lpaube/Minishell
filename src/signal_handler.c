/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:10:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/15 10:55:53 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

void	newline(int signal)
{
	(void)signal;
	ft_printf("\rminishell:   \n");
	rl_replace_line("", 1);
	if (g_minishell.allow_signal)
		rl_on_new_line();
	g_minishell.code = 130;
	rl_redisplay();
}

void	nothing(int signal)
{
	(void)signal;
	if (g_minishell.allow_signal)
		rl_on_new_line();
	else
		printf("\n");
	g_minishell.code = 0;
	rl_redisplay();
}
