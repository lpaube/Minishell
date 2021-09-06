/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 18:56:07 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/06 19:50:15 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "tokenizer.h"
#include "my_env.h"

static char	*output_code(void)
{
	return (ft_strdup("0"));
}

static char	*parse_variable(char **str)
{
	t_string	var_name;
	char		*var_value;

	var_name = ft_str_new(NULL);
	++(*str);
	if (**str == '?')
	{
		++(*str);
		return (output_code());
	}
	while (ft_isalnum(**str) || **str == '_')
	{
		ft_str_add_back(var_name, **str);
		++(*str);
	}
	var_value = ft_getenv(ft_str_data(var_name));
	ft_str_free(var_name);
	return (var_value);
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

char	*parse_special_chars(char *str)
{
	t_string	ret;
	t_state		state;
	char		*tmp;

	ret = ft_str_new(NULL);
	state = TEXT;
	while (*str)
	{
		if (*str == '$' && (state == TEXT || state == DQUOTE))
		{
			tmp = parse_variable(&str);
			if (tmp)
				ft_str_append_cstr(ret, tmp);
			continue ;
		}
		if (eval_quotes(&str, &state))
			continue ;
		ft_str_add_back(ret, *str);
		++str;
	}
	tmp = ft_strdup(ft_str_data(ret));
	ft_str_free(ret);
	free(str);
	return (tmp);
}
