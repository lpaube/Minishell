/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolation2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:36:48 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/16 21:31:49 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
