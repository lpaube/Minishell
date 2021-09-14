/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:10:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/12 15:50:56 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
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
