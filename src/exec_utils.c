/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:31:51 by laube             #+#    #+#             */
/*   Updated: 2021/09/14 16:28:32 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	env_new_var(char **res_table, char *new_arg, int *i)
{
	res_table[*i] = malloc((ft_strlen(new_arg) * sizeof(char)));
	ft_memcpy(res_table[*i], new_arg, ft_strlen(new_arg) + 1);
	(*i)++;
}

/*	Returns a malloc'd 2d duplicated table of env
 *	and updates it with new var if applicable	*/
char	**dup_env_table(char **table, char *env_var, int new_var)
{
	char	**res_table;
	int		i;
	char	*new_arg;

	new_arg = env_var;
	i = 0;
	while (table[i])
		i++;
	res_table = malloc((i + 1 + new_var) * sizeof(char *));
	if (!res_table)
		print_error("Could not malloc 'res_table'.");
	i = 0;
	while (table[i])
	{
		res_table[i] = malloc((ft_strlen(table[i]) + 1) * sizeof(char));
		if (!res_table[i])
			print_error("Could not malloc 'res_table[i]");
		ft_memcpy(res_table[i], table[i], ft_strlen(table[i]) + 1);
		i++;
	}
	if (new_var)
		env_new_var(res_table, new_arg, &i);
	table[i] = NULL;
	return (res_table);
}

char	*ft_getenv(char *var)
{
	char	*var_name;
	int		i;
	char	*ret;

	var_name = ft_strjoin(var, "=");
	i = 0;
	while (g_minishell.env[i])
	{
		if (ft_strnstr(g_minishell.env[i], var_name, ft_strlen(var_name)))
		{
			ret = (g_minishell.env[i] + ft_strlen(var_name));
			free(var_name);
			return (ret);
		}
		i++;
	}
	free(var_name);
	return (NULL);
}
