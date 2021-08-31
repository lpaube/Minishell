/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_center.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:29:29 by laube             #+#    #+#             */
/*   Updated: 2021/08/31 00:30:49 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_header.h"

void	operation_control(t_phrase *phrase)
{
	if (phrase->prev)
	{
		if (phrase->prev->op == '|')
		{
			pipe_read(phrase);
		}
	}
	if (phrase->next)
	{
		if (phrase->op == '|')
		{
			pipe_write(phrase);
		}
	}
}

void	execution_control(t_phrase *phrase)
{
	
	if (phrase->bin == 1)
	{
		ft_binary(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "echo", 5))
	{
		ft_echo(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "cd", 3))
	{
		ft_cd(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "pwd", 4))
	{
		ft_pwd(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "export", 7))
	{
		ft_export(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "unset", 6))
	{
		ft_unset(phrase);
	}
	else if (ft_strnstr(phrase->cmd, "env", 4))
	{
		ft_env(phrase);
	}
	/* Doesn't currently handle arguments */
	else if (ft_strnstr(phrase->cmd, "exit", 5))
	{
		ft_exit(phrase);
	}
}

/* Most functions don't correctly handle arguments of size 0 or > 1 */
int	main_control(t_phrase *phrase)
{
	while (phrase)
	{
		if (phrase->next || phrase->prev)
		{
			operation_control(phrase);
		}
		else
		{
			execution_control(phrase);
		}
		phrase = phrase->next;
	}
	return (0);
}
