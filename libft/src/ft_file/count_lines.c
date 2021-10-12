/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:05:29 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/01 02:03:52 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE (1024)
#endif

static ssize_t	count_newlines(const char *str)
{
	char	*newline;
	ssize_t	count;

	count = 0;
	newline = ft_strchr(str, '\n');
	while (newline)
	{
		newline = ft_strchr(newline + 1, '\n');
		++count;
	}
	return (count);
}

ssize_t	count_lines(const char *file)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	bytes;
	ssize_t	count;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	count = 0;
	bytes = BUFFER_SIZE;
	while (bytes == BUFFER_SIZE)
	{
		bytes = read(fd, &buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			close(fd);
			return (-1);
		}
		buf[bytes] = 0;
		count += count_newlines(buf);
	}
	close(fd);
	return (count);
}
