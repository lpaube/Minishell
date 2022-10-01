#include "parse.h"
#include "minishell.h"
#include <stdlib.h>

static void	add_status_code(t_string out)
{
	char	*num;

	num = ft_ltoa(g_mini.code);
	ft_str_append_cstr(out, num);
	free(num);
}

static void	parse_variable(char **str, t_string out)
{
	t_string	var_name;
	char		*var_value;

	if (**str == '?' || ft_isdigit(**str))
	{
		if (**str == '?')
			add_status_code(out);
		++(*str);
		return ;
	}
	if (!(ft_isalnum(**str) || **str == '_'))
	{
		ft_str_add_back(out, '$');
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
			str++;
			parse_variable(&str, ret);
			continue ;
		}
		if (eval_quotes(&str, &state))
			continue ;
		ft_str_add_back(ret, *str);
		++str;
	}
	tmp = ft_str_take(ret);
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
