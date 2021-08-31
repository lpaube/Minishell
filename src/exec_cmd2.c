/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:15:00 by laube             #+#    #+#             */
/*   Updated: 2021/08/31 00:34:24 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_header.h"

/*	Executes the binary entered as cmd */
int	ft_binary(t_phrase *phrase)
{
	char	*bin_path;
	pid_t	pid;

	bin_path = get_bin_path(phrase->env, phrase->cmd);
	if (bin_path == NULL)
		return (-1);
	pid = fork();
	if (pid == -1)
		ft_terminate(errno, "Invalid process id after fork.");
	if (pid == 0)
	{
		if (execve(bin_path, phrase->cmd_args, phrase->env) == -1)
			ft_terminate(errno, "Invalid execution of binary.");
	}
	wait(0);
	return (0);
}

void	ft_echo(t_phrase *phrase)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (ft_strnstr((phrase->cmd_args)[i], "-n", 2))
	{
		nl = 0;
		i++;
	}
	while ((phrase->cmd_args)[i])
	{
		printf("%s", (phrase->cmd_args[i]));
		i++;
		if ((phrase->cmd_args)[i])
			printf(" ");
	}
	if (nl)
		printf("\n");
}

void	ft_exit(t_phrase *phrase)
{
	exit(0);
}
