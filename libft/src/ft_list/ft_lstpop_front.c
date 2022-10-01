#include "libft.h"
#include <stdlib.h>

void	*ft_lstpop_front(t_list **lst)
{
	t_list	*tmp;
	void	*content;

	if (*lst)
	{
		tmp = (*lst)->next;
		content = (*lst)->content;
		free(*lst);
		*lst = tmp;
		return (content);
	}
	return (NULL);
}
