/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:31:51 by laube             #+#    #+#             */
/*   Updated: 2021/09/15 23:10:28 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include <stdlib.h>

char	*ft_getenv(char *var)
{
	char	*var_name;
	char	*ret;
	size_t	i;

	var_name = ft_strjoin(var, "=");
	i = 0;
	while (g_minishell.env[i])
	{
		if (ft_strncmp(g_minishell.env[i], var_name, ft_strlen(var_name)) == 0)
		{
			ret = g_minishell.env[i] + ft_strlen(var_name);
			free(var_name);
			return (ret);
		}
		i++;
	}
	free(var_name);
	return (NULL);
}

void	ft_setenv(const char *var, const char *value)
{
	size_t		i;
	t_string	env_value;
	bool		found;

	env_value = ft_str_new_copy(var);
	ft_str_add_back(env_value, '=');
	ft_str_append_cstr(env_value, value);
	found = false;
	i = 0;
	while (g_minishell.env[i])
	{
		if (ft_strncmp(g_minishell.env[i], var, ft_strlen(var)) == 0)
		{
			free(g_minishell.env[i]);
			g_minishell.env[i] = ft_str_take(env_value);
			found = true;
			break ;
		}
		++i;
	}
	if (!found)
		g_minishell.env
			= ft_expand_strarr(g_minishell.env, ft_str_take(env_value));
	ft_str_free(env_value);
}

char	*var_name(const char *var)
{
	t_string	name;
	char		*ptr;

	name = ft_str_new(NULL);
	ptr = ft_strchr(var, '=');
	if (!ptr)
		return (NULL);
	while (var != ptr)
		ft_str_add_back(name, *var++);
	ptr = ft_str_take(name);
	ft_str_free(name);
	return (ptr);
}
