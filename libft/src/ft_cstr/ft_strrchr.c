/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:54:25 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/06 01:16:51 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, char c)
{
	const char	*ptr;

	ptr = s + ft_strlen(s);
	while (s <= ptr)
	{
		if (*ptr == c)
			return ((char *)(ptr));
		--ptr;
	}
	return (NULL);
}
