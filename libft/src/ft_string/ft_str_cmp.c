/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 22:56:07 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/09 00:51:50 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_string.h"

int32_t	ft_str_cmp(const t_string s1, const t_string s2, size_t n)
{
	return (ft_strncmp(ft_str_data(s1), ft_str_data(s2), n));
}
