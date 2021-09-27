/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:31:51 by laube             #+#    #+#             */
/*   Updated: 2021/09/27 16:29:15 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*ft_getenv(const char *var)
{
	char	*var_name;
	char	*ret;
	size_t	i;

	var_name = ft_strjoin(var, "=");
	i = 0;
	while (g_mini.env[i])
	{
		if (ft_strncmp(g_mini.env[i], var_name, ft_strlen(var_name)) == 0)
		{
			ret = g_mini.env[i] + ft_strlen(var_name);
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
	char		*var_cpy;

	var_cpy = ft_strjoin(var, "=");
	env_value = ft_str_new_copy(var_cpy);
	ft_str_append_cstr(env_value, value);
	found = false;
	i = 0;
	while (g_mini.env[i])
	{
		if (ft_strncmp(g_mini.env[i], var_cpy, ft_strlen(var_cpy)) == 0)
		{
			free(g_mini.env[i]);
			g_mini.env[i] = ft_str_take(env_value);
			found = true;
			break ;
		}
		++i;
	}
	if (!found)
		g_mini.env = ft_strarr_extend(g_mini.env, ft_str_take(env_value));
	free(var_cpy);
}

char	*var_name(const char *var)
{
	t_string	name;
	char		*ptr;

	ptr = ft_strchr(var, '=');
	if (!ptr || ptr == var)
		return (NULL);
	name = ft_str_new(NULL);
	while (var != ptr)
		ft_str_add_back(name, *var++);
	return (ft_str_take(name));
}

bool	is_valid_var_name(const char *var)
{
	const char	*ptr;

	if (!var)
		return (false);
	ptr = var;
	while (*ptr)
	{
		if (!(ft_isalnum(*ptr) || *ptr == '_'))
			return (false);
		++ptr;
	}
	return (true);
}
