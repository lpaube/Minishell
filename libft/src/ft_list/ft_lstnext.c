#include "libft.h"

t_list	*ft_lstnext(t_list **lst)
{
	if (*lst)
	{
		*lst = (*lst)->next;
		return (*lst);
	}
	return (NULL);
}
