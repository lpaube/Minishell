/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:16:36 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/21 05:16:07 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <stdlib.h>

static t_redir	*new_redir(t_list **tokens)
{
	t_redir	*redir;
	char	*str;

	redir = ft_calloc(1, sizeof(t_redir));
	redir->type = get_type((*tokens)->content);
	ft_lstnext(tokens);
	str = ft_str_data((*tokens)->content);
	redir->file = ft_strdup(str);
	return (redir);
}

static t_node	*get_next_node(t_list **tokens)
{
	t_node	*node;
	char	*str;

	node = nodenew();
	while (*tokens && get_type((*tokens)->content) != PIPE)
	{
		str = ft_str_data((*tokens)->content);
		if (is_redirection(get_type((*tokens)->content)))
			ft_lstadd_back(&node->redirs,
				ft_lstnew((void *)new_redir(tokens)));
		else
			node->argv = ft_strarr_extend(node->argv, ft_strdup(str));
		ft_lstnext(tokens);
	}
	if (*tokens)
		ft_lstnext(tokens);
	return (node);
}

t_node	*parse(t_list *tokens)
{
	t_node	*cmds;

	if (!tokens)
		return (NULL);
	cmds = NULL;
	if (!is_valid_syntax(tokens))
		return (NULL);
	while (tokens)
		nodeadd_back(&cmds, get_next_node(&tokens));
	return (cmds);
}
