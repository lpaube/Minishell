/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:28:14 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/14 22:05:39 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H
# define NODE_H

# include "token.h"

typedef struct s_redir
{
	t_type	type;
	char	*file;
}	t_redir;

typedef struct s_node
{
	char			*cmd;
	char			**args;
	t_list			*redirs;
	int				*fd;
	int				output_fd;
	int				intput_fd;
	int				saved_stdout;
	int				saved_stdin;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

void		nodeclear(t_node **node);
void		nodeadd_back(t_node **lst, t_node *new);
t_node		*nodelast(t_node *lst);
t_node		*nodenew(void);

#endif
