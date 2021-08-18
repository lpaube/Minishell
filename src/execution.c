/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 14:50:36 by laube             #+#    #+#             */
/*   Updated: 2021/08/18 14:52:25 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"

/*	Finds the PATH variable,
	then returns the full binary path of the binary */
char	*get_bin_path(char **envp, char *cmd)
{
	char	*path;

	while (*envp)
	{
		path = ft_strnstr(*envp, "PATH=", 5);
		if (path != NULL)
			return (validate_path(path, cmd));
		envp++;
	}
	return (NULL);
}
void	ft_binary(t_parse *parse)
{
	char	*bin_path;

	bin_path = get_bin_path(parse->env, parse->cmd);

}

int	execution_control(t_parse *parse)
{
	if (parse->bin == 1)
		ft_binary(parse);
}