/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 20:45:52 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/01 00:55:40 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE (1024)
#endif

ssize_t	file_size(const char *file)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes;
	ssize_t	size;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	size = 0;
	bytes = BUFFER_SIZE;
	while (bytes == BUFFER_SIZE)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			close(fd);
			return (-1);
		}
		size += bytes;
	}
	return (size);
}
