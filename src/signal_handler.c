/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:10:13 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/03 16:58:24 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <readline/readline.h>

void	newline(int signal)
{
	(void)signal;
	ft_printf("\n");
	// rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	nothing(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}
