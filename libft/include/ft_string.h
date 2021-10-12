/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 22:13:17 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/29 10:33:29 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stddef.h>

# define INITIAL_CAPACITY 12

typedef struct s_string_
{
	char	*data;
	size_t	capacity;
	size_t	len;
}	t_string_;

#endif
