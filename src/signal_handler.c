/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:10:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/08 23:51:14 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

void	newline(int signal)
{
	(void)signal;
	ft_printf("\n");
	rl_replace_line("", 1);
	if (g_minishell.allow_signal)
		rl_on_new_line();
	rl_redisplay();
}

void	nothing(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}
