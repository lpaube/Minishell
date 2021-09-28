/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:37:15 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/28 09:46:22 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

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
