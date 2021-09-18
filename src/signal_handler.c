/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:10:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 20:35:31 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "print.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdio.h>

void	newline(int signal)
{
	(void)signal;
	printf("\r" C_RED SHELL_NAME "%%" C_RST "  \n");
	rl_replace_line("", 1);
	if (g_mini.allow_signal)
		rl_on_new_line();
	g_mini.code = 130;
	rl_redisplay();
}

void	nothing(int signal)
{
	(void)signal;
	if (g_mini.allow_signal)
		rl_on_new_line();
	else
		printf("\n");
	g_mini.code = 0;
	rl_redisplay();
}
