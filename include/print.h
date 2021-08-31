/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:41:41 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/31 01:43:24 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "libft.h"
# include "operator.h"
# include "node.h"

void	print_token_list(const t_list *lst);
char	*op_name(t_operator op);
void	print_args(char **args);
void	print_nodes(const t_node *lst);

#endif
