#ifndef NODE_H
# define NODE_H

# include "tokenizer.h"

typedef struct s_redir
{
	t_type	type;
	char	*file;
}	t_redir;

typedef struct s_node
{
	char			**argv;
	t_list			*redirs;
	int				fd[2];
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

void		nodeclear(t_node **node);
void		nodeadd_back(t_node **lst, t_node *new);
t_node		*nodelast(t_node *lst);
t_node		*nodenew(void);

#endif
