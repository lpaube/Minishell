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
