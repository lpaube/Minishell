/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:33:20 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/09 00:52:00 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <limits.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE (1024)
#endif

#ifndef OPEN_MAX
# define OPEN_MAX (256)
#endif

static void	free_and_set(char **ptr, char *value)
{
	free(*ptr);
	*ptr = value;
}

static int32_t	read_file(char	**file_buffer, int fd)
{
	char		read_buffer[BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		bytes;

	bytes = read(fd, read_buffer, BUFFER_SIZE);
	if (bytes == -1)
		return (-1);
	read_buffer[bytes] = '\0';
	tmp = ft_strjoin(*file_buffer, read_buffer);
	if (!tmp)
		return (-1);
	free_and_set(file_buffer, tmp);
	if (bytes < BUFFER_SIZE)
		return (0);
	return (1);
}

static int32_t	get_line(char **buffer, char **line)
{
	char	*tmp;
	char	*newline;

	newline = ft_strchr(*buffer, '\n');
	if (!newline)
		*line = ft_strdup(*buffer);
	else
		*line = ft_substr(*buffer, 0, (size_t)newline - *(size_t *)buffer);
	if (!*line)
		return (-1);
	if (!newline)
	{
		free_and_set(buffer, NULL);
		return (0);
	}
	else
	{
		tmp = ft_substr(*buffer, (uint32_t)ft_strlen(*line) + 1, BUFFER_SIZE);
		if (!tmp)
			return (-1);
		free_and_set(buffer, tmp);
		return (1);
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*buffer[OPEN_MAX] = {NULL};
	int			code;

	if (!line)
		free_and_set(&buffer[fd], NULL);
	if (fd < 0 || fd >= OPEN_MAX || !line)
		return (-1);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	code = 1;
	while (!ft_strchr(buffer[fd], '\n'))
	{
		code = read_file(&buffer[fd], fd);
		if (code < 1)
			break ;
	}
	if (code == -1)
	{
		free_and_set(&buffer[fd], NULL);
		return (-1);
	}
	return (get_line(&buffer[fd], line));
}
