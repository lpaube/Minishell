/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 23:11:20 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/27 20:34:58 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft.h"
# include "operator.h"

typedef struct s_construct
{
	char		*name;
	char		**args;
	bool		is_cmd;
	t_operator	op;
}	t_construct;

t_tree	*parse(t_list *token_lst);
void	free_construct(void *c);

#endif
