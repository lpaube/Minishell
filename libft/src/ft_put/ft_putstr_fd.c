#include "libft.h"

void	ft_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
