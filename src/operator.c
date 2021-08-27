/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 04:14:19 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/27 04:23:42 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator.h"

t_operator	get_operator(t_string str)
{
	if (ft_strncmp(ft_str_data(str), "|", ft_str_len(str)) == 0)
		return (PIPE);
	if (ft_strncmp(ft_str_data(str), "<", ft_str_len(str)) == 0)
		return (INPUT);
	if (ft_strncmp(ft_str_data(str), "<<", ft_str_len(str)) == 0)
		return (READ);
	if (ft_strncmp(ft_str_data(str), ">", ft_str_len(str)) == 0)
		return (OUTPUT);
	if (ft_strncmp(ft_str_data(str), ">>", ft_str_len(str)) == 0)
		return (APPEND);
	return (NONE);
}
