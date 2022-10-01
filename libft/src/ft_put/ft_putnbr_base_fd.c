#include "libft.h"

static void	putnbr_recursive(int64_t n, const char *base, int radix, int fd)
{
	int64_t	index;

	if (n < 0 && n / radix == 0)
		ft_putchar_fd('-', fd);
	if (n / radix != 0)
		putnbr_recursive(n / radix, base, radix, fd);
	if (n < 0)
	{
		index = (n % radix) * -1;
		ft_putchar_fd(base[index], fd);
	}
	else
		ft_putchar_fd(base[n % radix], fd);
}

void	ft_putnbr_base_fd(int64_t n, const char *base, int fd)
{
	putnbr_recursive(n, base, (int)ft_strlen(base), fd);
}
