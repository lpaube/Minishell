#include "libft.h"

static void	ft_ntoa_base(char *b, int64_t n, size_t len, const char *base)
{
	int64_t	base_len;
	int64_t	i;

	base_len = (int64_t)ft_strlen(base);
	if (n < 0)
		*b++ = '-';
	while (len > 0)
	{
		i = n % base_len;
		if (i < 0)
			i *= -1;
		b[--len] = base[i];
		n /= base_len;
	}
}

char	*ft_ltoa_base(int64_t n, const char *base)
{
	char	*ret;
	size_t	len;
	size_t	size;
	size_t	base_len;

	base_len = ft_strlen(base);
	len = ft_numlen(n, (int64_t)base_len);
	size = len + 1;
	if (n < 0)
		size += 1;
	ret = ft_calloc(size, sizeof(char));
	if (!ret)
		return (NULL);
	ft_ntoa_base(ret, n, len, base);
	return (ret);
}
