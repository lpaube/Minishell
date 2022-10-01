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
