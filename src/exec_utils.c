/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:31:51 by laube             #+#    #+#             */
/*   Updated: 2021/08/31 00:34:58 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tmp_header.h"

void	ft_terminate(int err, char *err_str)
{
	char	*ret_str;

	if (err != 0)
		ret_str = strerror(err);
	else
		ret_str = err_str;
	printf("%s\n", err_str);
	exit(0);
}

/*	Returns a malloc'd 2d duplicated table of env
 *	and updates it with new var if applicable	*/
char	**dup_env_table(char **table, t_phrase *phrase, int new_var)
{
	char	**res_table;
	int		i;
	char	*new_arg;

	new_arg = phrase->cmd_args[1];
	i = 0;
	while (table[i])
		i++;
	res_table = malloc((i + 1 + new_var) * sizeof(char *));
	if (!res_table)
		ft_terminate(errno, "Could not malloc 'res_table'.");
	i = 0;
	while (table[i])
	{
		res_table[i] = malloc((ft_strlen(table[i]) + 1) * sizeof(char));
		if (!res_table[i])
			ft_terminate(errno, "Could not malloc 'res_table[i]");
		ft_memcpy(res_table[i], table[i], ft_strlen(table[i]) + 1);
		i++;
	}
	if (new_var)
	{
		res_table[i] = malloc((ft_strlen(new_arg) * sizeof(char)));
		ft_memcpy(res_table[i], new_arg, ft_strlen(new_arg) + 1);
		i++;
	}
	table[i] = NULL;
	return (res_table);
}

/*	Receives a malloc'd str, and returns a new malloc'd str
 *	with appended char	*/
char	*ft_append_str(char **str, char c)
{
	char	*new_str;
	int		i;

	new_str = malloc((ft_strlen(*str) + 1) * sizeof(char));
	i = 0;
	while ((*str)[i])
	{
		new_str[i] = (*str)[i];
		i++;
	}
	new_str[i] = c;
	i++;
	new_str[i] = 0;
	//free(*str);
	return (new_str);
}
