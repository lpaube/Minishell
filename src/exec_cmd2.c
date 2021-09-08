/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:15:00 by laube             #+#    #+#             */
/*   Updated: 2021/09/08 18:57:18 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

/*	Executes the binary entered as cmd */
int	ft_binary(void)
{
	char	*bin_path;
	pid_t	pid;

	bin_path = get_bin_path(g_minishell.env, g_minishell.phrase->name);
	if (bin_path == NULL)
		return (-1);
	pid = fork();
	if (pid == -1)
		print_error("Invalid process id after fork.");
	if (pid == 0)
	{
		if (execve(bin_path, g_minishell.phrase->args, g_minishell.env) == -1)
			print_error("Invalid execution of binary.");
	}
	wait(0);
	return (0);
}

void	ft_echo(void)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if ((g_minishell.phrase->args)[i] && ft_strnstr((g_minishell.phrase->args)[i], "-n", 2))
	{
		nl = 0;
		i++;
	}
	while ((g_minishell.phrase->args)[i])
	{
		printf("%s", (g_minishell.phrase->args[i]));
		i++;
		if ((g_minishell.phrase->args)[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
}

void	ft_exit(void)
{
	exit(0);
}
