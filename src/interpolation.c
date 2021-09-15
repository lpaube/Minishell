/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:56:07 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/15 10:57:15 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"
#include <stdlib.h>

static void	output_code(t_string out)
{
	char	*num;

	num = ft_itoa(g_minishell.code);
	ft_str_append_cstr(out, num);
	free(num);
}

static void	parse_variable(char **str, t_string out)
{
	t_string	var_name;
	char		*var_value;

	++(*str);
	if (**str == '?')
	{
		++(*str);
		output_code(out);
		return ;
	}
	var_name = ft_str_new(NULL);
	while (ft_isalnum(**str) || **str == '_')
	{
		ft_str_add_back(var_name, **str);
		++(*str);
	}
	var_value = ft_getenv(ft_str_data(var_name));
	ft_str_free(var_name);
	if (var_value)
		ft_str_append_cstr(out, var_value);
}

static bool	eval_quotes(char **str, t_state *state)
{
	if (**str == '\'' && *state != DQUOTE)
	{
		if (*state == TEXT)
			*state = QUOTE;
		else if (*state == QUOTE)
			*state = TEXT;
		++(*str);
		return (true);
	}
	else if (**str == '\"' && *state != QUOTE)
	{
		if (*state == TEXT)
			*state = DQUOTE;
		else if (*state == DQUOTE)
			*state = TEXT;
		++(*str);
		return (true);
	}
	return (false);
}

char	*interpolate(char *str)
{
	t_string	ret;
	t_state		state;
	char		*tmp;
	char		*ptr;

	ptr = str;
	ret = ft_str_new(NULL);
	state = TEXT;
	while (*str)
	{
		if (*str == '$' && (state == TEXT || state == DQUOTE))
		{
			parse_variable(&str, ret);
			continue ;
		}
		if (eval_quotes(&str, &state))
			continue ;
		ft_str_add_back(ret, *str);
		++str;
	}
	tmp = ft_str_take(ret);
	ft_str_free(ret);
	free(ptr);
	return (tmp);
}

void	interpolate_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		arr[i] = interpolate(arr[i]);
		++i;
	}
}
