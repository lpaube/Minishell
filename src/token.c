/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:37:15 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 21:15:38 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_type	get_type(t_string token)
{
	if (ft_strncmp(ft_str_data(token), "|", ft_str_len(token)) == 0)
		return (PIPE);
	if (ft_strncmp(ft_str_data(token), "<", ft_str_len(token)) == 0)
		return (INPUT);
	if (ft_strncmp(ft_str_data(token), "<<", ft_str_len(token)) == 0)
		return (HEREDOC);
	if (ft_strncmp(ft_str_data(token), ">", ft_str_len(token)) == 0)
		return (OUTPUT);
	if (ft_strncmp(ft_str_data(token), ">>", ft_str_len(token)) == 0)
		return (APPEND);
	return (STRING);
}

bool	is_redirection(t_type type)
{
	if (type == OUTPUT || type == APPEND
		|| type == INPUT || type == HEREDOC)
		return (true);
	return (false);
}

char	*type_str(t_type type)
{
	if (type == OUTPUT)
		return ("OUTPUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == INPUT)
		return ("INPUT");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == PIPE)
		return ("PIPE");
	return ("STRING");
}
