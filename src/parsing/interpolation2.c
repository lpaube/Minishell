#include "parse.h"

static	void	interpolate_redir(void *redir)
{
	t_redir	*r;

	r = redir;
	r->file = interpolate(r->file);
}

void	interpolate_redirs(t_list *redirs)
{
	ft_lstiter(redirs, interpolate_redir);
}
