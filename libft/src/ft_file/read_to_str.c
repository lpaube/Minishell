/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 18:25:38 by mleblanc          #+#    #+#             */
/*   Updated: 2021/10/01 01:00:17 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE (1024)
#endif

char	*cleanup_and_exit(int fd, t_string str)
{
	close(fd);
	ft_str_free(str);
	return (NULL);
}

char	*read_to_str(const char *file)
{
	char		buffer[BUFFER_SIZE + 1];
	int			fd;
	ssize_t		bytes;
	t_string	content;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	content = ft_str_new(NULL);
	if (!content)
		cleanup_and_exit(fd, content);
	bytes = BUFFER_SIZE;
	while (bytes == BUFFER_SIZE)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			cleanup_and_exit(fd, content);
		buffer[bytes] = '\0';
		if (!ft_str_append_cstr(content, buffer))
			cleanup_and_exit(fd, content);
	}
	close(fd);
	return (ft_str_take(content));
}
